#include <stdio.h>
#include <string.h>
#include <stdlib.h>

enum tokenType {
    ttUnknown,
    ttCLASS,
    ttACCESS_MODE,
    ttSTATIC,
    ttRETURN,
    ttNAME,
    ttSTRING,
    ttSIGN,
    ttNUMBER,
    ttLEFT_BRACKET,
    ttRIGHT_BRACKET,
    ttEQUALS,
    ttLEFT_BRACK,
    ttRIGHT_BRACK,
    ttPOINT,
    ttCOMMA,
    ttEND,
    ttBOOL,
    ttFOR,
    ttDO,
    ttWHILE,
    ttAPOSTROPHE
};

int count = 0;
char s[100][100] = {
    {"class Program {"},
       {" static void Main(string args) "},
       {"{"},
            {"System.Console.WriteLine(\"Привет мир!\");"},
            {"System.Console.ReadLine();"},
            {"Int a = f;"},
            {"D = a + b;"},
            {"Ldl = 102;"},
            {"System.Console.WriteLine(asd + asdf);"},
            {"char c = 'a';"},
            {"while (g) {"},
            {"}"},
            {"bool g = true;"},
            {"kdjskdlf(lksjdfl);"},
            {"float m = 12.6;"},
            {"dkk();"},
            {"}"},

   {" int fun() {"},
           {" Ksdfj slkdfj;"},
           {" Ksdjf = lkjsd + ldakjf;"},
           {" return 0;"},
   {" }"},
  {"  }"},

};

void copy(char*, char*);

void start(int, char*, int);

int term(enum tokenType);

enum tokenType getTokenType(char*);

int checkClass(void);

int checkDirection(void);

void checkMode(void);

int checkVariable(void);

int checkFunction(void);

int checkCallFunction(void);

int funcArguments(void);

int funcCallArguments(void);

int mathCount(void);

int main() {
    int size = count;
    count = 0;
    int correct = 1;
    while (count < size && correct) {
        correct = checkClass();
    }
    if (correct)
        printf_s("correct\n");
    if (!correct) {
        printf_s("uncorrect\n");
    }
}

void copy(char to[], char src[]) {
    for (int i = 0; i < strlen(src); i++)
        to[i] = src[i];
}


enum tokenType getTokenType(char* token) {
    if (!(strcmp(token, "class"))) return ttCLASS;
    else if (!(strcmp(token, "public") && strcmp(token, "private") && strcmp(token, "protected"))) return ttACCESS_MODE;
    else if (!strcmp(token, "static")) return ttSTATIC;
    else if (!strcmp(token, "return")) return ttRETURN;
    else if (!strcmp(token, "while")) return ttWHILE;
    else if (!strcmp(token, "do")) return ttDO;
    else if (!strcmp(token, "for")) return ttFOR;
    else if (!strcmp(token, "name")) return ttNAME;
    else if (!strcmp(token, "num")) return ttNUMBER;
    else if (!strcmp(token, "string")) return ttSTRING;
    else if (!strcmp(token, "sign")) return ttSIGN;
    else if (!strcmp(token, "(")) return ttLEFT_BRACKET;
    else if (!strcmp(token, ")")) return ttRIGHT_BRACKET;
    else if (!strcmp(token, "{")) return ttLEFT_BRACK;
    else if (!strcmp(token, "}")) return ttRIGHT_BRACK;
    else if (!strcmp(token, "=")) return ttEQUALS;
    else if (!strcmp(token, ",")) return ttCOMMA;
    else if (!strcmp(token, ".")) return ttPOINT;
    else if (!strcmp(token, ";")) return ttEND;
    else if (!strcmp(token, "'")) return ttAPOSTROPHE;
    return ttUnknown;
}

int term(enum tokenType expected) {
    if (getTokenType(s[count]) == expected) {
        count++;
        return 1;
    }
    return 0;
}


int checkClass() {
    //    s = line;
    //    count = num;
    if (term(ttCLASS) && term(ttNAME) && term(ttLEFT_BRACK)) {
        while (1) {
            checkMode();
            if (!(checkVariable() || checkFunction())) {
                break;
            }
            if (term(ttRIGHT_BRACK)) {
                return 1;
            }
        }
        return 0;
    }
    return 0;
}

void checkMode() {
    int temp = count;
    enum tokenType possibleModeAccess = getTokenType(s[temp]);
    if (possibleModeAccess == ttACCESS_MODE) {
        temp++;
        possibleModeAccess = getTokenType(s[temp]);
    }

    if (possibleModeAccess == ttSTATIC) {
        temp++;
        possibleModeAccess = getTokenType(s[temp]);
    }

    count = temp;
}

int checkWhile() {

    if (term(ttWHILE) && term(ttLEFT_BRACKET) && term(ttNAME) && term(ttRIGHT_BRACKET) && term(ttLEFT_BRACK)) {
        int i = 0;
        while (i < 40) {
            if (getTokenType(s[i]) == term(ttRIGHT_BRACK)) {
                return 0;
            }
            i++;
        }
        return 1;
    }
    return 0;
};

int checkDoWhile() {
    int temp = count;

    if (term(ttDO) && term(ttLEFT_BRACK)) {
        int i = 0;
        while (i < 40) {
            if (getTokenType(s[i]) == term(ttRIGHT_BRACK)) {
                if (term(ttWHILE) && term(ttLEFT_BRACKET) && term(ttNAME) && term(ttRIGHT_BRACKET) && term(ttEND)) {
                    return 0;
                }
            }
            i++;
        }
        return 1;

    }
    return 0;
}

int checkFor() {
    if (term(ttFOR) && term(ttLEFT_BRACKET) && checkVariable() && term(ttEND) && term(ttNAME) && term(ttEND) &&
        term(ttNAME) && term(ttRIGHT_BRACKET) && term(ttLEFT_BRACK)) {
        int i = 0;
        while (i < 40) {
            if (getTokenType(s[i]) == term(ttRIGHT_BRACK)) {
                return 0;
            }
            i++;
        }
        return 1;
    }
    return 0;
}

int checkCycle() {
    return checkWhile() && checkDoWhile() && checkFor();
}

int checkFunction() {
    int temp = count;
    //    functuion
    if (term(ttNAME) && term(ttNAME) && term(ttLEFT_BRACKET) && funcArguments() && term(ttLEFT_BRACK)) {
        int res = 1;
        while (1 && res) {
            checkDirection();
            if (!(checkCycle() || checkCallFunction() || checkVariable())) {
                res = 0;
            }
            if (term(ttRETURN)) {
                if (getTokenType(s[count]) == ttNAME || getTokenType(s[count]) == ttNUMBER ||
                    getTokenType(s[count]) == ttSTRING) {
                    count++;
                    if (term(ttEND) && term(ttRIGHT_BRACK))
                        return 1;
                }
            }
            if (term(ttRIGHT_BRACK)) {
                return 1;
            }
        }
    }
    count = temp;
    return 0;
}

int checkDirection() {
    while (getTokenType(s[count + 1]) == ttPOINT) {
        count += 2;
    }
    if (getTokenType(s[count]) == ttNAME) {
        return 1;
    }

    return 0;
}

int funcArguments() {
    switch (getTokenType(s[count])) {
    case ttRIGHT_BRACKET:
        count++;
        return 1;
    case ttCOMMA:
        count++;
        if (getTokenType(s[count]) != ttNAME) {
            return 0;
        }
    case ttNAME:
        count++;
        if (getTokenType(s[count]) != ttNAME) {
            return 0;
        }
        count++;
        return funcArguments();
    }
    return 0;
}

int checkVariable() {
    int temp = count;
    //    variable mode access static name;
    if (term(ttNAME) && term(ttNAME) && term(ttEND)) {
        return 1;
    }

    count = temp;
    if (term(ttNAME) && term(ttEQUALS)) {
        switch (getTokenType(s[count])) {
        case ttNAME:
        case ttNUMBER:
            count++;
            return mathCount() && term(ttEND);
        case ttBOOL:
        case ttSTRING:
            count++;
            return term(ttEND);
        case ttAPOSTROPHE:
            count += 2;
            return term(ttEND);
        }
    }

    count = temp;
    //    variable mode access static name = name|number^operations|"string";
    if (term(ttNAME) && term(ttNAME) && term(ttEQUALS)) {
        switch (getTokenType(s[count])) {
        case ttNAME:
            count++;
            return term(ttEND);
        case ttNUMBER:
            count++;
            return mathCount() && term(ttEND);
        case ttSTRING:
            count++;
            return term(ttEND);
        }
        return 1;
    }
    count = temp;
    return 0;
}

int checkCallFunction() {
    int temp = count;
    if (term(ttNAME) && term(ttLEFT_BRACKET)) {
        switch (getTokenType(s[count])) {
        case ttRIGHT_BRACKET:
            count++;
            if (getTokenType(s[count]) == ttEND) {
                count++;
                return 1;
            }
            return 0;
        default:
            return funcCallArguments();
        }
    }
    count = temp;
    return 0;
}

int funcCallArguments() {
    switch (getTokenType(s[count])) {
    case ttRIGHT_BRACKET:
        count++;
        if (getTokenType(s[count]) == ttEND) {
            count++;
            return 1;
        }
        return 0;
    case ttCOMMA:
        count++;
        if (!(getTokenType(s[count]) != ttNUMBER || getTokenType(s[count]) != ttNAME ||
            getTokenType(s[count]) != ttSTRING)) {
            return 0;
        }
        count--;
    case ttNAME:
    case ttSTRING:
        count++;
        //            return funcCallArguments();
    case ttNUMBER:
        if (mathCount()) {
            return funcCallArguments();
        }
        return 0;
    }
    return 0;
}

int mathCount() {
    switch (getTokenType(s[count])) {
    case ttRIGHT_BRACKET:
    case ttEND:
    case ttCOMMA:
        return 1;
    case ttSIGN:
        count++;
        if (getTokenType(s[count]) != ttNUMBER && getTokenType(s[count]) != ttNAME) {
            return 0;
        }
    case ttNUMBER:
    case ttNAME:
        count++;
        return mathCount();
    }
    return 0;
}
