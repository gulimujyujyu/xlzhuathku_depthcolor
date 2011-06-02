#include "FileValidator.h"
#include <QString>
#include <QDir>

FileValidator::FileValidator(void)
{
}

FileValidator::FileValidator(QString re, QString dir)
{
	this->setRegExpStr(re);
	this->setDir(dir);
}

FileValidator::FileValidator(const char* re, const char * dir)
{
	this->setRegExpStr(re);
	this->setDir(dir);
}

FileValidator::~FileValidator(void)
{
}

void FileValidator::setRegExpStr(const char *re)
{
	this->regexpStr = QString(QLatin1String(re));
}

void FileValidator::setRegExpStr(QString re)
{
	this->regexpStr = re;
}

void FileValidator::setDir(const char *dir)
{
	QString dirName = QString(QLatin1String(dir));
	this->currentDir = QDir(dirName);
}

void FileValidator::setDir(QString dir)
{
	QString dirName = dir;
	this->currentDir = QDir(dirName);
}

QString FileValidator::findFileInDir()
{
	if ( !(this->currentDir.exists()))	{
		return QString();
	}
	QStringList flist = this->currentDir.entryList();
	QRegExp re(this->regexpStr);
	for (int i=0; i<flist.size(); i++) {
		if (re.exactMatch(flist[i])) {
			return this->currentDir.absolutePath() + QString("/") + flist[i];
		}
	}
	return QString();
}