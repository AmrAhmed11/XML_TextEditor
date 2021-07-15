#ifndef BASIC_XML_SYNTAX_HIGHLIGHTER_H
#define BASIC_XML_SYNTAX_HIGHLIGHTER_H

#include <QSyntaxHighlighter>
#include <QTextEdit>
#include <QPlainTextEdit>

class BasicXMLSyntaxHighlighter : public QSyntaxHighlighter
{
    Q_OBJECT
public:
    BasicXMLSyntaxHighlighter(QTextEdit * parent);

protected:
    virtual void highlightBlock(const QString & text);

private:
    void highlightByRegex(const QTextCharFormat & format,
                          const QRegExp & regex, const QString & text);

    void setRegexes();
    void setFormats();

private:
    QTextCharFormat     m_xmlKeywordFormat;
    QTextCharFormat     m_xmlElementFormat;
    QTextCharFormat     m_xmlAttributeFormat;
    QTextCharFormat     m_xmlValueFormat;
    QTextCharFormat     m_xmlCommentFormat;
    QTextCharFormat     m_xmlError1Format;
    QTextCharFormat     m_xmlError2Format;


    QList<QRegExp>      m_xmlKeywordRegexes;
    QRegExp             m_xmlElementRegex;
    QRegExp             m_xmlAttributeRegex;
    QRegExp             m_xmlValueRegex;
    QRegExp             m_xmlCommentRegex;
    QRegExp             m_xmlError1Regex;
    QRegExp             m_xmlError2Regex;
};

#endif // BASIC_XML_SYNTAX_HIGHLIGHTER_H
