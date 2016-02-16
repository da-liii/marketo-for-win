#include <QCoreApplication>
#include <QFile>
#include <QFileInfo>
#include <QString>
#include <QRegularExpression>
#include <QDebug>
#include <QCommandLineParser>

QString link(const QString &path, const QString &fileName)
{
    QFile in(QStringLiteral("%1/%2").arg(path, fileName));
    if (!in.open(QIODevice::ReadOnly)) {
        qDebug() << "failed to read" << path << fileName << in.fileName();
        return QString();
    }

    QString firstLine = in.readLine();
    if (firstLine.isEmpty()) {
        qDebug() << in.fileName() << "line could not be read...";
        return QString();
    }
    QRegularExpression fNameReg(QStringLiteral("(.*\\.(?:svg|png|gif|ico))"));
    QRegularExpressionMatch match = fNameReg.match(firstLine);
    if (!match.hasMatch()) {
        return QString();
    }

    QFileInfo linkInfo(QStringLiteral("%1/%2").arg(path, match.captured(1)));
    QString aliasLink = link(linkInfo.path(), linkInfo.fileName());
    if (!aliasLink.isEmpty()) {
        //qDebug() <<  fileName << "=" << match.captured(1) << "=" << aliasLink;
        return aliasLink;
    }

    return  QStringLiteral("%1/%2").arg(path, match.captured(1));
}

int parseFile(const QString &infile, const QString &outfile)
{
    QFile in(infile);
    QFile out(outfile);
    QRegularExpression imageReg(QStringLiteral("<file>(.*\\.(?:svg|png|gif|ico))</file>"));

    if (!in.open(QIODevice::ReadOnly)) {
        qDebug() << "Failed to open" << infile;
        return -1;
    }
    if (!out.open(QIODevice::WriteOnly)) {
        qDebug() << "Failed to create" << outfile;
        return -2;
    }

    while (in.bytesAvailable()) {
        QString line = QString::fromLocal8Bit(in.readLine());
        QRegularExpressionMatch match = imageReg.match(line);
        if (!match.hasMatch()) {
            //qDebug() << "No Match: " << line;
            out.write(qPrintable(line));
            continue;
        }

        QFileInfo info(match.captured(1));


        QString aliasLink = link(info.path(), info.fileName());
        if (aliasLink.isEmpty()) {
            //qDebug() << "No alias: " << line;
            out.write(qPrintable(line));
            continue;
        }

        QString newLine = QStringLiteral("<file alias=\"%1\">%2</file>\n").arg(match.captured(1), aliasLink);
        //qDebug() << newLine;
        out.write(qPrintable(newLine));
    }
    return 0;
}


int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    QCommandLineParser parser;

    QCommandLineOption inOption(QStringList() << QLatin1String("i") << QLatin1String("infile"), QStringLiteral("Input qrc file"), QStringLiteral("infile"));
    QCommandLineOption outOption(QStringList() << QLatin1String("o") << QLatin1String("outfile"), QStringLiteral("Output qrc file"), QStringLiteral("outfile"));
    parser.addHelpOption();
    parser.addVersionOption();
    parser.addOption(inOption);
    parser.addOption(outOption);
    parser.process(app);

    const QString inName = parser.value(inOption);
    const QString outName = parser.value(outOption);

    qDebug() << inName << outName;

    return parseFile(inName, outName);
}
