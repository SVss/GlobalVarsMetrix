#ifndef REGEXES_H_
#define REGEXES_H_

#include <QRegularExpression>

typedef const QRegularExpression ConstRegExp;

#define NEW_CONST_REG(name, reg) ConstRegExp name = QRegularExpression(reg)
#define NEW_CONST_REG_PARAMS(name, reg, params) const QRegularExpression name = QRegularExpression(reg, params)

#define DOT_ALL QRegularExpression::DotMatchesEverythingOption


NEW_CONST_REG(RX_WHITE_SPACES, "\\s+");

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

NEW_CONST_REG(RX_STRING_LITERALS, "'([^']+|'')*'");


NEW_CONST_REG(RX_SINGLELINE_COMMENTS, "\\/\\/.*");
NEW_CONST_REG_PARAMS(RX_MULTILINE_COMMENTS, "{.*?}|\\(\\*.*?\\*\\)", DOT_ALL );


NEW_CONST_REG(RX_FORWARD_DECL,"(\\bprocedure\\b|\\bfunction\\b)\\s*[\\w]+\\s*"\
                              "(\\(.*?\\)\\s*|):?\\s*([\\w]+|)\\s*;\\s*forward\\s*;");

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

NEW_CONST_REG_PARAMS(RX_BLOCK, "(?:\\bprocedure\\b|\\bfunction\\b).*?(?:\\bend\\b\\s*;\\s*"\
                               "(?=\\bvar\\b|\\bconst\\b|\\bprocedure\\b|\\bfunction\\b|\\bbegin\\b|"
                               "\\btype\\b))", DOT_ALL);

NEW_CONST_REG_PARAMS(RX_MAIN, ("\\bbegin.*?\\bend\\s*."), DOT_ALL);

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

NEW_CONST_REG_PARAMS(RX_VAR_TYPE_SECTION, "\\b(?<=var|type)\\b(.*?)\\b(?=begin|type|procedure|function|"\
                                          "const|var|type)\\b", DOT_ALL);
const uint VAR_TYPE_SECTION_GROUP = 0;

NEW_CONST_REG_PARAMS(RX_ENUMERATED, "[^\\w]\\((.*?)\\)", DOT_ALL);
const uint ENUMERATED_GROUP = 1;

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

NEW_CONST_REG_PARAMS(RX_VAR_SECTION, "\\bvar\\b(.*?)\\b(?=begin|type|procedure|function|const|var|type)\\b", DOT_ALL);
const uint VAR_SECTION_GROUP = 0;

NEW_CONST_REG(RX_VAR_IDS, "(?<=\\bvar\\b|;)\\s*([\\w,\\s]*?)\\s*(?::)" );
const uint VAR_IDS_GROUP = 1;

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

NEW_CONST_REG_PARAMS(RX_TYPE_SECTION, "\\btype\\b(.*?)\\b(?=begin|type|procedure|function|const|var)\\b", DOT_ALL);
const uint TYPE_SECTION_GROUP = 0;

NEW_CONST_REG_PARAMS(RX_LOCAL_TYPES, "(?<=\\btype|;)\\s*(.*?)=", DOT_ALL);
const uint LOCAL_TYPES_GROUP = 1;

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

NEW_CONST_REG_PARAMS(RX_CAPTION, "(\\bprocedure\\b|\\bfunction\\b)\\s*[\\w][\\w\\d]*\\s*(\\(.*?\\)\\s*|):?"\
                                 "\\s*([\\w][\\w\\d]*|)\\s*;", DOT_ALL);
const uint CAPTION_GROUP = 2;

NEW_CONST_REG_PARAMS(RX_CAPTION_PARAMS, "(\\(|;)\\s*(.*?(?=(\\)|:)))", DOT_ALL);
const uint CAPTION_PARAMS_GROUP = 2;

NEW_CONST_REG_PARAMS(RX_PARAM_OPERATORS, "\\b(var|const|type|out)\\b", DOT_ALL);


NEW_CONST_REG_PARAMS(RX_VAR_CONST_SECTION, "\\b(var|const)\\b(.*?)\\b(?=begin|type|procedure|function|const|var|type)\\b", DOT_ALL);
const uint VAR_CONST_SECTION_GROUP = 0;

NEW_CONST_REG_PARAMS(RX_VAR_CONST_IDENTIFIERS, "(?:\\b(?:var|const)\\b|;)\\s*([\\w,\\s]*)\\s*(?:|:=)", DOT_ALL);
const uint VAR_CONST_IDENTIFIERS_GROUP = 1;

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#define BLOCK_MARK "\n\nprocedure ___\n\n"
NEW_CONST_REG(RX_BLOCK_MARK, BLOCK_MARK);

// ->

const QRegularExpression makeListRegExp(QStringList list);

#endif // REGEXES_H_
