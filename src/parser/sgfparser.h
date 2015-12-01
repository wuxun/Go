#ifndef SGFPARSER_H
#define SGFPARSER_H

class QTextStream;

class SgfParser
{
public:
    SgfParser();

    void doParse(QTextStream &in);
};

#endif // SGFPARSER_H
