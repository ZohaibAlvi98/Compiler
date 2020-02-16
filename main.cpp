#include <iostream>
#include<fstream>
#include<string>
#include<regex>
#include<map>
#include<stack>

using namespace std;
string keyArray[]={"var","loop_if","loop_else","loop_for","loop_while","end_loop","class","ret","func","secure","local","protected","void","main"};
string opArray[]={"=","+","-","*","/","%","<",">","!"};
string DoubOp[]={"<=",">=","!=","==~","&&","||","++","--","/*","*/","->"};
string Punc[]={"{","}","(",")","[","]","\,",";",":","//"};
string tokenFile="TokenFile";
int counter=0;
int s=0;
string currClass="";
char lineChange='\n';

 stack <int> ss;

void createScope()
{
    if(ss.empty())
    {
        ss.push(s);
    }
    else
    {
    s++;
    ss.push(s);
    }
}

void destroy()
{
    if(!ss.empty())
    {
        ss.pop();
    }
}

struct symbolTable
{
    string name;
    string type;
    int scope;
};

symbolTable* ST = nullptr;

struct classDataTable
{
    string am;
    string type;
    string name;

};

struct dataTable
{
    string name;
    string type;
    string parent;
    classDataTable* CDT = nullptr;

};

dataTable* DT = nullptr;

struct syntaxCheck
{
    string clasPart;
    string valuePart;
    int lineNo;
};
syntaxCheck* arr = nullptr;
syntaxCheck* temparr = nullptr;
int lineno=1;
int z=0;
int x=0;
string temp="";
string classPart(string val)
{
   regex intr("([+|-]?[0-9]+)");
    if(regex_match(val,intr))
    {
        return "int_const";
    }
    regex id("([A-Za-z]+)|([A-Za-z]+_[A-Za-z]+)|([A-Za-z]+[0-9]+)|([A-Za-z]+_[0-9]+)|([A-Za-z]+_.*)");
    if(regex_match(val,id))
    {
        return "id";
    }
    regex floatr("(\\+[0-9]+\\.[0-9]+)|(-[0-9]+\\.[0-9]+)|(\\+\\.[0-9]+)|(-\\.[0-9]+)|(\\.[0-9]+)|([0-9]+\\.[0-9]+)");
if(regex_match(val,floatr))
    {
        return "float_const";
    }
    regex str("(\".*\")");
    if(regex_match(val,str))
    {
        return "string";
    }

regex func("([A-Za-z]+\\(\\))|([A-Za-z]+_[A-Za-z]+\\(\\))|([A-Za-z]+[0-9]+\\(\\))|([A-Za-z]+_[0-9]+\\(\\))");
if(regex_match(val,func))
    {
        return "function";
    }
     return "invalid lexeme";
}


void writeInFile(string word);

void checkKeyword(string a)
{
    if(a=="var")
    {
        cout<<"classpart is var : "<<lineno<<endl;
        temparr[counter].clasPart="var";
        temparr[counter].lineNo=lineno;
        counter++;
        tokenFile+=lineChange;
        tokenFile+="var";
        tokenFile+=lineChange;
        tokenFile+=to_string(lineno);

    }
    else if(a=="loop_if")
    {
        cout<<"classpart is loop_if"<<lineno<<endl;
        temparr[counter].clasPart="loop_if";
        temparr[counter].lineNo=lineno;
        counter++;
        tokenFile+=lineChange;
        tokenFile+="loop_if";
        tokenFile+=lineChange;
        tokenFile+=to_string(lineno);


    }
    else if(a=="loop_else")
    {
        cout<<"classpart is loop_else : "<<lineno<<endl;
        temparr[counter].clasPart="loop_else";
        temparr[counter].lineNo=lineno;
        counter++;
        tokenFile+=lineChange;
         tokenFile+="loop_else";
         tokenFile+=lineChange;
        tokenFile+=to_string(lineno);

    }
    else if(a=="loop_for")
    {
        cout<<"classpart is loop_for : "<<lineno<<endl;
        temparr[counter].clasPart="loop_for";
        temparr[counter].lineNo=lineno;
        counter++;
        tokenFile+=lineChange;
         tokenFile+="loop_for";
         tokenFile+=lineChange;
        tokenFile+=to_string(lineno);

    }
    else if(a=="loop_while")
    {
        cout<<"classpart is loop_while : "<<lineno<<endl;
        temparr[counter].clasPart="loop_while";
        temparr[counter].lineNo=lineno;
        counter++;
        tokenFile+=lineChange;
        tokenFile+="loop_while";
        tokenFile+=lineChange;
        tokenFile+=to_string(lineno);

    }
    else if(a=="end_loop")
    {
        cout<<"classpart is end_loop : "<<lineno<<endl;
        temparr[counter].clasPart="end_loop";
        temparr[counter].lineNo=lineno;
        counter++;
        tokenFile+=lineChange;
        tokenFile+="end_loop";
        tokenFile+=lineChange;
        tokenFile+=to_string(lineno);

    }
    else if(a=="class")
    {
        cout<<"classpart is class : "<<lineno<<endl;
        temparr[counter].clasPart="class";
        temparr[counter].lineNo=lineno;
        counter++;
        tokenFile+=lineChange;
        tokenFile+="class";
        tokenFile+=lineChange;
        tokenFile+=to_string(lineno);

    }
    else if(a=="ret")
    {
        cout<<"classpart is ret  :"<<lineno<<endl;
        temparr[counter].clasPart="ret";
        temparr[counter].lineNo=lineno;
        counter++;
        tokenFile+=lineChange;
         tokenFile+="ret";
         tokenFile+=lineChange;
        tokenFile+=to_string(lineno);
    }
    else if(a=="func")
    {
        cout<<"classpart is func : "<<lineno<<endl;
        temparr[counter].clasPart="func";
        temparr[counter].lineNo=lineno;
        counter++;
        tokenFile+=lineChange;
         tokenFile+="func";
         tokenFile+=lineChange;
        tokenFile+=to_string(lineno);
    }
    else if(a=="protected")
    {
        cout<<"classpart is protected : "<<lineno<<endl;
        temparr[counter].clasPart="protected";
        temparr[counter].lineNo=lineno;
        counter++;
        tokenFile+=lineChange;
       tokenFile+="protected";
       tokenFile+=lineChange;
        tokenFile+=to_string(lineno);
    }
    else if(a=="secure")
    {
        cout<<"classpart is secure : "<<lineno<<endl;
        temparr[counter].clasPart="secure";
        temparr[counter].lineNo=lineno;
        counter++;
        tokenFile+=lineChange;
       tokenFile+="secure";
       tokenFile+=lineChange;
        tokenFile+=to_string(lineno);
    }
    else if(a=="local")
    {
        cout<<"classpart is local : "<<lineno<<endl;
        temparr[counter].clasPart="local";
        temparr[counter].lineNo=lineno;
        counter++;
        tokenFile+=lineChange;
        tokenFile+="local";
        tokenFile+=lineChange;
        tokenFile+=to_string(lineno);

    }
    else if(a=="<")
    {
        cout<<"classpart is Relational op : "<<lineno<<endl;
        temparr[counter].clasPart="Relational Op";
        temparr[counter].lineNo=lineno;
        counter++;
        tokenFile+=lineChange;
        tokenFile+="Relational op";
        tokenFile+=lineChange;
        tokenFile+=to_string(lineno);

    }
    else if(a==">")
    {
        cout<<"classpart is Relational op : "<<lineno<<endl;
        temparr[counter].clasPart="Relational Op";
        temparr[counter].lineNo=lineno;
        counter++;
        tokenFile+=lineChange;
       tokenFile+="Relational op";
       tokenFile+=lineChange;
        tokenFile+=to_string(lineno);

    }
    else if(a=="<=")
    {
        cout<<"classpart is Relational op : "<<lineno<<endl;
        temparr[counter].clasPart="Relational Op";
        temparr[counter].lineNo=lineno;
        counter++;
        tokenFile+=lineChange;
       tokenFile+="Relational op";
       tokenFile+=lineChange;
        tokenFile+=to_string(lineno);


    }
    else if(a==">=")
    {
        cout<<"classpart is Relational op : "<<lineno<<endl;
        temparr[counter].clasPart="Relational Op";
        temparr[counter].lineNo=lineno;
        counter++;
        tokenFile+=lineChange;
        tokenFile+="Relational op";
        tokenFile+=lineChange;
        tokenFile+=to_string(lineno);

    }
    else if(a=="!=")
    {
        cout<<"classpart is Relational op : "<<lineno<<endl;
        temparr[counter].clasPart="Relational Op";
        temparr[counter].lineNo=lineno;
        counter++;
        tokenFile+=lineChange;
        tokenFile+="Relational op";
        tokenFile+=lineChange;
        tokenFile+=to_string(lineno);

    }
    else if(a=="==")
    {
        cout<<"classpart is Relational op : "<<lineno<<endl;
        temparr[counter].clasPart="Relational Op";
        temparr[counter].lineNo=lineno;
        counter++;
        tokenFile+=lineChange;
       tokenFile+="Relational op";
       tokenFile+=lineChange;
        tokenFile+=to_string(lineno);

    }
    else if(a=="+")
    {
        cout<<"classpart is PM : "<<lineno<<endl;
        temparr[counter].clasPart="PM";
        temparr[counter].lineNo=lineno;
        counter++;
        tokenFile+=lineChange;
        tokenFile+="PM";
        tokenFile+=lineChange;
        tokenFile+=to_string(lineno);

    }
    else if(a=="-")
    {
        cout<<"classpart is PM : "<<lineno<<endl;
        temparr[counter].clasPart="PM";
        temparr[counter].lineNo=lineno;
        counter++;
        tokenFile+=lineChange;
        tokenFile+="PM";
        tokenFile+=lineChange;
        tokenFile+=to_string(lineno);

    }
    else if(a=="*")
    {
        cout<<"classpart is MDM : "<<lineno<<endl;
        temparr[counter].clasPart="MDM";
        temparr[counter].lineNo=lineno;
        counter++;
        tokenFile+=lineChange;
         tokenFile+="MDM";
         tokenFile+=lineChange;
        tokenFile+=to_string(lineno);

    }
    else if(a=="/")
    {
        cout<<"classpart is MDM : "<<lineno<<endl;
        temparr[counter].clasPart="MDM";
        temparr[counter].lineNo=lineno;
        counter++;
        tokenFile+=lineChange;
         tokenFile+="MDM";
         tokenFile+=lineChange;
        tokenFile+=to_string(lineno);

    }
    else if(a=="%")
    {
        cout<<"classpart is MDM : "<<lineno<<endl;
        temparr[counter].clasPart="MDM";
        temparr[counter].lineNo=lineno;
        counter++;
        tokenFile+=lineChange;
        tokenFile+="MDM";
        tokenFile+=lineChange;
        tokenFile+=to_string(lineno);

    }
    else if(a=="&&")
    {
        cout<<"classpart is Logical op : "<<lineno<<endl;
        temparr[counter].clasPart="and";
        temparr[counter].lineNo=lineno;
        counter++;
        tokenFile+=lineChange;
         tokenFile+="Logical op";
         tokenFile+=lineChange;
        tokenFile+=to_string(lineno);

    }
    else if(a=="||")
    {
        cout<<"classpart is Logical op : "<<lineno<<endl;
        temparr[counter].clasPart="or";
        temparr[counter].lineNo=lineno;
        counter++;
        tokenFile+=lineChange;
        tokenFile+="Logical op";
        tokenFile+=lineChange;
        tokenFile+=to_string(lineno);

    }
    else if(a=="!")
    {
        cout<<"classpart is Unary op : "<<lineno<<endl;
        temparr[counter].clasPart="!";
        temparr[counter].lineNo=lineno;
        counter++;
        tokenFile+=lineChange;
        tokenFile+="Logical op";
        tokenFile+=lineChange;
        tokenFile+=to_string(lineno);

    }
    else if(a=="++")
    {
        cout<<"classpart is Increment : "<<lineno<<endl;
        temparr[counter].clasPart="++";
        temparr[counter].lineNo=lineno;
        counter++;
        tokenFile+=lineChange;
        tokenFile+="Increment";
        tokenFile+=lineChange;
        tokenFile+=to_string(lineno);

    }
    else if(a=="--")
    {
        cout<<"classpart is Decrement : "<<lineno<<endl;
        temparr[counter].clasPart="--";
        temparr[counter].lineNo=lineno;
        counter++;
        tokenFile+=lineChange;
        tokenFile+="Decrement";
        tokenFile+=lineChange;
        tokenFile+=to_string(lineno);

    }
    else if(a=="{")
    {
        cout<<"classpart is Curly Bracket Open : "<<lineno<<endl;
        temparr[counter].clasPart="Open Curly Bracket";
        temparr[counter].lineNo=lineno;
        counter++;
        tokenFile+=lineChange;
        tokenFile+="Curly Bracket Open";
        tokenFile+=lineChange;
        tokenFile+=to_string(lineno);

    }
    else if(a=="}")
    {
        cout<<"classpart is Curly Bracket close : "<<lineno<<endl;
         temparr[counter].clasPart="Close Curly Bracket";
        temparr[counter].lineNo=lineno;
        counter++;
        tokenFile+=lineChange;
         tokenFile+="Curly Bracket close";
         tokenFile+=lineChange;
        tokenFile+=to_string(lineno);

    }
    else if(a=="(")
    {
        cout<<"classpart is Round Bracket Open : "<<lineno<<endl;
         temparr[counter].clasPart="Round Bracket Open";
        temparr[counter].lineNo=lineno;
        counter++;
        tokenFile+=lineChange;
         tokenFile+="Round Bracket Open";
         tokenFile+=lineChange;
        tokenFile+=to_string(lineno);

    }
    else if(a==")")
    {
        cout<<"classpart is Round Bracket close : "<<lineno<<endl;
         temparr[counter].clasPart="Round Bracket Close";
        temparr[counter].lineNo=lineno;
        counter++;
        tokenFile+=lineChange;
         tokenFile+="Round Bracket close";
         tokenFile+=lineChange;
        tokenFile+=to_string(lineno);
    }
    else if(a=="[")
    {
        cout<<"classpart is Square Bracket open : "<<lineno<<endl;
         temparr[counter].clasPart="Open Square Bracket";
        temparr[counter].lineNo=lineno;
        counter++;
        tokenFile+=lineChange;
         tokenFile+="Square Bracket Open";
         tokenFile+=lineChange;
        tokenFile+=to_string(lineno);

    }
    else if(a=="]")
    {
        cout<<"Square Bracket close"<<lineno<<endl;
         temparr[counter].clasPart="Close Square Bracket";
        temparr[counter].lineNo=lineno;
        counter++;
        tokenFile+=lineChange;
         tokenFile+="Square Bracket Close";
         tokenFile+=lineChange;
        tokenFile+=to_string(lineno);
    }
    else if(a==",")
    {
        cout<<"classpart is comma : "<<lineno<<endl;
         temparr[counter].clasPart="comma";
        temparr[counter].lineNo=lineno;
        counter++;
         tokenFile+="Comma";
        tokenFile+=to_string(lineno);
        tokenFile+=lineChange;
    }
   else if(a==":")
    {
        cout<<"classpart is Colon : "<<lineno<<endl;
         temparr[counter].clasPart="colon";
        temparr[counter].lineNo=lineno;
        counter++;
        tokenFile+=lineChange;
         tokenFile+="Colon";
         tokenFile+=lineChange;
        tokenFile+=to_string(lineno);
    }
    else if(a=="->")
    {
        cout<<"classpart is arrow pointer : "<<lineno<<endl;
         temparr[counter].clasPart="->";
        temparr[counter].lineNo=lineno;
        counter++;
        tokenFile+=lineChange;
         tokenFile+="arrow pointer";
         tokenFile+=lineChange;
        tokenFile+=to_string(lineno);

    }
    else if(a=="=")
    {
        cout<<"as op : "<<lineno<<endl;
         temparr[counter].clasPart="as_op";
        temparr[counter].lineNo=lineno;
        counter++;
        tokenFile+=lineChange;
         tokenFile+="as_op";
         tokenFile+=lineChange;
        tokenFile+=to_string(lineno);
    }
    else if(a==";")
    {
        cout<<"semi_colon op : "<<lineno<<endl;
         temparr[counter].clasPart=";";
        temparr[counter].lineNo=lineno;
        counter++;
        tokenFile+=lineChange;
         tokenFile+="Semi_colon op";
         tokenFile+=lineChange;
        tokenFile+=to_string(lineno);
        lineno+=1;
    }
    else if(a=="void")
    {
      cout<<"void : "<<lineno<<endl;
         temparr[counter].clasPart="void";
        temparr[counter].lineNo=lineno;
        counter++;
        tokenFile+=lineChange;
         tokenFile+="void";
         tokenFile+=lineChange;
        tokenFile+=to_string(lineno);
    }
     else if(a=="main")
    {
      cout<<"main : "<<lineno<<endl;
         temparr[counter].clasPart="main";
        temparr[counter].lineNo=lineno;
        counter++;
        tokenFile+=lineChange;
         tokenFile+="main";
         tokenFile+=lineChange;
        tokenFile+=to_string(lineno);
    }
    else if(a=="/*")
    {
        cout<<"Open Comments : "<<lineno<<endl;
    }
    else if(a=="*/")
    {
        cout<<"close Comments : "<<lineno<<endl;

    }
    else if(a!="var")
    {
        string s=classPart(a);
        temparr[counter].clasPart=s;
        temparr[counter].lineNo=lineno;
        counter++;
        tokenFile+=lineChange;
        tokenFile+=s;
        tokenFile+=lineChange;
        tokenFile+=to_string(lineno);
        cout<<s<<lineno<<endl;
    }
else if(a=="@")
    {
        cout<<a<<endl;
        temparr[counter].valuePart=a;
        temparr[counter].clasPart="Invalid lexeme";
        temparr[counter].lineNo=lineno;

        tokenFile+=a;
        tokenFile+="Invalid lexeme";
        tokenFile+=to_string(lineno);
        tokenFile+=lineChange;
        cout<<"invalid lexeme : "<<lineno<<endl;
    }


}

void keywordsArray(string a)
{
    int i=0;
    while(a==keyArray[i])
    {
        i++;
    }
    checkKeyword(a);
}

bool checkId_const(string a, string b)
{
    string d=a+b;
    regex id("([A-Za-z]+)|([A-Za-z]+_[A-Za-z]+)|([A-Za-z]+[0-9]+)|([A-Za-z]+_[0-9]+)|([A-Za-z]+_.*)");
    if(regex_match(d,id))
    {
        return true;
    }
    return false;
}

bool checkFloatIntRegex(string temp, string b,string a)
{
    string d=temp+b;
    int i=0;
    regex intre("([0-9]+\\.[0-9]+)|([0-9]+\\.)|([+|-|\\.]?[0-9]+)");
    if(regex_match(d,intre))
    {
        return true;
    }

    return false;

}

bool checking(string a, string b,string next)
{
    string d;
    d=b+next;
    //cout<<d<<endl;

    for(int j=0;j<11;j++)
    {
        if(d==DoubOp[j])
        {
            if(temp!="")
            {
            cout<<temp<<endl;
            temparr[counter].valuePart=temp;
            tokenFile+=lineChange+temp;
            keywordsArray(temp);
            }
            z++;
            temp=d;
            return true;
        }
    }
    for(int i=0;i<8;i++)
    {
        if(b==opArray[i])
        {
            if(temp!="")
            {
            cout<<temp<<endl;
            temparr[counter].valuePart=temp;
             tokenFile+=lineChange+temp;
            keywordsArray(temp);
            }
            temp=b;
            return true;
        }
    }

    regex func("([A-Za-z]+\\(\\))|([A-Za-z]+_[A-Za-z]+\\(\\))|([A-Za-z]+[0-9]+\\(\\))|([A-Za-z]+_[0-9]+\\(\\))");
if(regex_match(b,func))
    {
        return false;
    }
     return false;
}

bool checkPunc(string temp,string b)
{

 for(int k=0;k<11;k++)
    {
        if(b==Punc[k])
        {
            if(temp!="")
            {
                cout<<temp<<endl;
                temparr[counter].valuePart=temp;
                 tokenFile+=lineChange+temp;
                keywordsArray(temp);

             }


      /*  if(b==";")
       {
        lineno+=1;
       }*/
            return true;
        }
    }
return false;
}

void lexicalAnalyzer(string a)
{
    while(z!=a.length()){
   // string temp="";

    string c="";
    string Next_index="";
    //string NextNext_index="";
    int j=0;
    int y=0;
    string b=" ";
    //cout<<a.length()<<endl;
    while(a[z]!=b[j])
    {
        c=a[z];
        //cout<<"c"<<c<<endl;
        Next_index=a[z+1];
       //cout<<Next_index<<endl;
        string prev="";

        if(c=="\\" && Next_index=="n")
        {
             if(temp!="")
                {
                  cout<<temp<<endl;
                   tokenFile+=lineChange+temp;
                  keywordsArray(temp);
                  temp="";
                }
                z+=2;
            continue;
        }

///   for comments work

         if(c=="/")
        {
            z++;
            int TrackLineNO=lineno;
            string temporary="";
            temporary=a[z];
            prev=c;
            if(temporary=="/")
            {
                if(temp!="")
                {
                  cout<<temp<<endl;
                  temparr[counter].valuePart=temp;
                   tokenFile+=lineChange+temp;
                  keywordsArray(temp);
                  temp="";
                }
                while(temporary!="n" || prev!="\\")
                {
                    temp+=prev;
                    prev=temporary;
                    z++;
                    temporary=a[z];
                }
                //temp+=prev+temporary;
                cout<<"commented"<<endl;
                cout<<temp<<":"<<lineno<<endl;
                temp="";
                z++;
                continue;
            }
            if(temporary=="*")
            {
                if(temp!="")
                {
                    cout<<temp<<endl;
                    temparr[counter].valuePart=temp;
                     tokenFile+=lineChange+temp;
                    keywordsArray(temp);
                    temp="";
                }
                while(temporary!="/" || prev!="*")
                {
                temp+=prev;
                prev=temporary;
                z++;
                if(z==a.length())
                {
                    break;
                }
                temporary=a[z];
                }
                 //temp+=prev+temporary;
            cout<<"commented"<<endl;
            cout<<temp<<" : "<<endl;
            temp="";
            z++;
            if(z<=a.length())
            {
            continue;
            }
            else
            {
                exit(1);
            }
            }
            else
            {
                z--;
            }

            }

/// for string work

        if(c=="\"")
        {

            cout<<temp;
            if(temp!="")
            {
                cout<<temp<<endl;
                temparr[counter].valuePart=temp;
                 tokenFile+=lineChange+temp;
                keywordsArray(temp);
                temp="";
            }
            prev=c;
            z++;
            c=a[z];
            while(c!="\"" || prev=="\\")
            {
                temp+=prev;
                prev=c;
                z++;
                c=a[z];
                if(c=="n" && prev =="\\")
                {
                    break;
                }
            }
            temp+=prev+c;
            cout<<temp<<endl;
            temparr[counter].valuePart=temp;
             tokenFile+=lineChange+temp;
            keywordsArray(temp);
            z++;
            temp="";
            continue;
        }

/// for operator and double operator

        if(checking(temp,c,Next_index))
        {
            cout<<temp<<endl;
            temparr[counter].valuePart=temp;
            tokenFile+=lineChange+temp;
            keywordsArray(temp);
            z++;
            temp="";
            y=0;
            continue;
        }

        /// for punctuator

        if(checkPunc(temp,c))
        {
            temp=a[z];
            cout<<temp<<endl;
            temparr[counter].valuePart=temp;
             tokenFile+=lineChange+temp;
            keywordsArray(temp);
            temp="";
            z++;
            continue;
        }

        /// for identifier work

        if(checkId_const(temp,c))
        {
            temp+=c;
            //cout<<temp<<"temp"<<endl;
            z++;
            y=0;
            continue;
        }

        /// for float integer work

        if(checkFloatIntRegex(temp,c,Next_index))
        {
                 temp+=a[z];
                 z++;
                 continue;
        }

        /// for . operator error

        if(c=="\.")
        {

            //cout<<"invalid lexeme" <<endl;
             temparr[counter].valuePart+=temp;
             temparr[counter].valuePart+=c;
             tokenFile+=lineChange+temp;
              tokenFile+=c;
            cout<<temp<<c;
            z++;
             tokenFile+=a[z];
              temparr[counter].valuePart+=a[z];
            cout<<a[z];
            z++;
            c=a[z];
             while(c=="\.")
             {
                   temparr[counter].valuePart+=c;
                  tokenFile+=c;
                 cout<<c;
                 z++;
                  temparr[counter].valuePart+=a[z];
                  tokenFile+=a[z];
                 cout<<a[z];
                 z++;
                 c=a[z];
             }
               temparr[counter].clasPart="invalid lexeme";
            temparr[counter].lineNo=lineno;
            counter++;
             tokenFile+=lineChange;
              tokenFile+="invalid lexeme";
               tokenFile+=lineChange;
               tokenFile+=to_string(lineno);
                tokenFile+=lineChange;
             cout<<endl<<"invalid lexeme"<<endl;
            temp="";
            //z++;
        }
        else
        {
             temparr[counter].valuePart=temp;
            temparr[counter].clasPart="invalid lexeme";
            temparr[counter].lineNo=lineno;
            counter++;
            tokenFile+=lineChange;
            tokenFile+=temp;
            tokenFile+=lineChange;
            tokenFile+="invalid lexeme";
             tokenFile+=lineChange;
             tokenFile+=to_string(lineno);
             tokenFile+=lineChange;
            cout<<temp<<endl;
            cout<<"invalid lexeme";
            cout<<lineno<<endl;
            z++;
            temp="";
        }


    }
/// for space work

    if(a[z]==b[j])
    {
    z+=1;

    //cout<<"temp"<<temp<<endl;
   if(temp!="")
   {
       cout<<temp<<endl;
       tokenFile+=" "+temp;
    keywordsArray(temp);
    }
    //cout<<"temp"<<temp<<endl;
    temp="";
    y=0;
    }

}
}




int check=0;

bool start();
bool definitions();
bool MST();
bool dec(string am);
bool class_dec();
bool SST();
bool func_array_dec();
bool class_list();
bool class_body();
bool loop_if();
bool loop_for();
bool loop_while();
bool class_pointer();
bool obj_to_obj();
bool same_ids();
bool possibilities_5(string t);
bool argument_body();
bool aglist();
bool func_body();
bool modifiers();
bool ids();
bool access_modifiers();
bool possibilities_6();
bool left_openb();
bool possibilities_8();
bool bracketbody();
bool constructorlist();
bool cond();
bool loop_if_body();
bool loop_else_if();
bool loop();
bool loops();
bool loop_body();
bool c1();
bool c3();
bool non_terminal();
bool func_call();
bool possibilities();
bool class_obj_para_func_call();
bool inc_dec_op();
bool possibilities_2();
bool function_parameter();
bool func_paralist();
bool next_parameter();
bool class_obj_para();
bool array_dec(string t);
bool possibilities_4(string n, string t);
bool list(string n,string t);
bool init();
bool array_possibilities();
bool list2();
bool arraysize();
bool arraysize_2d();
bool possibilities_3();
bool left();
bool array_body();
bool array_list4();
bool array_list3();
bool array_list2();
bool array_and_list();
bool list_work();
bool array_list_work();
bool ret();
bool oe();
bool ae();
bool oe_();
bool ae_();
bool rope();
bool rope_();
bool e();
bool t();
bool f();
bool sameids2();
bool uop();
bool id_func();
bool func_work();
bool e_();
bool t_();
bool possibilities_7();
bool global_class_dec();
bool constructor();
bool constructor_access_modifier_dec();
bool c2();
bool oe_n();
bool non_terminal2();
bool class_obj_dec();
bool id_nt();
bool in_func_call();
bool thiss_oe();
bool obj_dec();

string lookupCDT(string n,string &am);
bool insertCDT(string n,string t, string accessm);
bool insertST(string n,string t,int s);
bool lookupST(string n,int s);
bool lookupST(string n);
string lookupDT(string n);
bool insertDT(string n,string t,string p);


    int countt=0;

bool syntaxAnalyzer(int sizee) {

    arr = new syntaxCheck[counter];

    ST = new symbolTable[counter];
    DT = new dataTable[counter];

for(int i=0;i<counter;i++)
{

    arr[i].valuePart=temparr[i].valuePart;
    arr[i].clasPart=temparr[i].clasPart;
    arr[i].lineNo=temparr[i].lineNo;

}
/*
    arr[counter].lineNo = lineno;
    arr[counter].clasPart = "$";
    arr[counter].valuePart = "$";
*/
delete temparr;
delete [] temparr;
/*
for(int u=0;u<counter;u++)
    {
        cout<<arr[u].valuePart<<endl;
        cout<<arr[u].clasPart<<endl;
        cout<<arr[u].lineNo<<endl;

    }*/

    if(start())
    {
        if(arr[countt].clasPart == "$")
        {
            countt++;
            cout<<endl<<endl<<"valid syntax"<<endl;
            return true;
        } else{
            cout << "document not parse fully";
            return false;
        }
    }
    cout << "Invalid syntax at "<< temparr[countt].lineNo << ": " <<  arr[countt].valuePart<< endl;
    return false;

/*
for(int i=0;i<counter;i++)
{
     cout<<endl;
     //cout<<arr[i].valuePart<<endl;
     cout<<realArr[i].valuePart<<endl;
     cout<<realArr[i].clasPart<<endl;
     cout<<realArr[i].lineNo<<endl;
}*/
}

bool start() {
  if(arr[countt].clasPart=="var" || arr[countt].clasPart=="class" || arr[countt].clasPart=="func" || arr[countt].clasPart=="void")
   {
     createScope();
   if(definitions())
    {
    if(arr[countt].clasPart=="void")
    {
      countt++;
      if(arr[countt].clasPart=="main")
      {
       countt++;
         if(arr[countt].clasPart=="Round Bracket Open")
         {
            countt++;
         if(arr[countt].clasPart=="Round Bracket Close")
         {
             countt++;
             if(arr[countt].clasPart=="Open Curly Bracket")
             {
                 createScope();
                 countt++;
                 if(MST())
                 {
                     destroy();
                    if(arr[countt].clasPart=="Close Curly Bracket")
                    {
                        countt++;
                        if(definitions())
                        {
                            return true;
                        }
                    }

                    }
                 }
             }
         }

      }


}
}
    }

    return false;
}

bool global_class_dec()
{
     if(arr[countt].clasPart=="var" || arr[countt].clasPart=="class" || arr[countt].clasPart=="func")
   {
       string am="";
    if(dec(am))
    {
        return true;
    }
    else if(class_dec())
    {
        return true;
    }
   }
    return false;
}

bool definitions()
{
   if(arr[countt].clasPart=="var" || arr[countt].clasPart=="class" || arr[countt].clasPart=="func")
   {

    if(global_class_dec())
    {
        if(definitions())
        {
            return true;
        }
    }
   }
    else if(arr[countt].clasPart=="void" || arr[countt].clasPart=="$")
    {
        return true;
    }
    return false;
}

bool MST()
{
    if(arr[countt].clasPart=="loop_if" || arr[countt].clasPart=="var"||arr[countt].clasPart=="loop_while" || arr[countt].clasPart=="this" || arr[countt].clasPart=="id" || arr[countt].clasPart=="ret" || arr[countt].clasPart==";" || arr[countt].clasPart=="func")
    {
        if(SST())
    {
        if(MST())
        {
            return true;
        }
    }
    }
    else if(arr[countt].clasPart=="Close Curly Bracket")
    {
        return true;
    }
    return false;
}

bool dec(string am)
{
    if(arr[countt].clasPart=="var" || arr[countt].clasPart=="func")
    {
 if(func_array_dec(am))
 {
     return true;
 }
    }
 return false;
}

int clas = 0;
int noAtt = 0;
string p="";
bool class_dec()
{
    if(arr[countt].clasPart=="class")
    {
   if(arr[countt].clasPart=="class")
   {
       countt++;
       if(arr[countt].clasPart=="id")
       {
           string n=arr[countt].valuePart;
           currClass=arr[countt].valuePart;
           string am="";

           countt++;
           if(class_list(am))
           {
               if(!insertDT(n,"class",p))
               {
                   cout<<"redecleration"<<endl;
               }
               if(arr[countt].clasPart=="Open Curly Bracket")
               {
                   countt++;
                   if(class_body(am))
                   {
                      if(arr[countt].clasPart=="Close Curly Bracket")
                      {
                          countt++;
                          return true;
                      }
                   }
               }
           }
       }
   }
   }
   return false;
}

bool SST()
{
    if(arr[countt].clasPart=="loop_if" || arr[countt].clasPart=="var"||arr[countt].clasPart=="loop_while" || arr[countt].clasPart=="this" || arr[countt].clasPart=="id" || arr[countt].clasPart=="ret" || arr[countt].clasPart==";" || arr[countt].clasPart=="func" || arr[countt].clasPart=="loop_for")
    {
        string am="";
    if(dec(am))
    {
        return true;
    }
    else if(loop_if())
    {
        return true;
    }
    else if(loop_while())
    {
        return true;
    }
    else if(loop_for())
    {
        return true;
    }
    else if(class_pointer(am))
    {
        return true;
    }
    else if(same_ids(am))
    {
        return true;
    }
    else if(ret(am))
    {
        return true;
    }
    else if(arr[countt].clasPart==";")
    {
        countt++;
        return true;
    }
    }
    return false;
}

bool func_array_dec(string am)
{
    if(arr[countt].clasPart=="var" || arr[countt].clasPart=="func")
    {
  if(arr[countt].clasPart=="var")
  {
      string t = arr[countt].clasPart;
      countt++;
      if(possibilities_5(am,t))
      {
          return true;
      }
  }
  else if(arr[countt].clasPart=="func")
  {
      countt++;
      if(arr[countt].clasPart=="id")
      {
          string n=arr[countt].valuePart;
          countt++;
          if(arr[countt].clasPart=="Round Bracket Open")
          {
              createScope();
              countt++;
              if(argument_body())
              {
                  if(arr[countt].clasPart=="Round Bracket Close")
                  {
                      if(!insertDTFN(n,"",pl))
                      {
                          cout<<"redeclaration error"<<endl;
                      }
                      countt++;
                      if(func_body())
                      {
                          return true;
                      }
                  }
              }
          }
      }
  }
    }
  return false;
}

bool class_list(string am,string p)
{
    if(arr[countt].clasPart=="colon")
    {
   if(arr[countt].clasPart=="colon")
   {
       countt++;
       if(modifiers(am))
       {
           if(arr[countt].clasPart=="id")
           {
               p=arr[countt].valuePart;
               countt++;
               string t = lookupDT(p);
               if(t=="")
               {
                   p="";
                   cout<<"undeclared"<<endl;
               }
               if(t!="class")
               {
                   p="";
                   cout<<"wrong type for inheritance"<<endl;
               }
               return true;
           }
       }
   }
    }
   else if(arr[countt].clasPart=="Open Curly Bracket")
    {
        return true;
    }
    return false;
}

int pl=0;
/*
bool constructor(string t1,string am)
{
    if(arr[countt].clasPart=="id")
    {
    if(arr[countt].clasPart=="id")
    {
        string n=arr[countt].valuePart;
        if(n!=currClass)
        {
            cout<<"wrong type for constructor"<<endl;
        }
        countt++;
        if(arr[countt].clasPart=="Round Bracket Open")
        {
            createScope();
            countt++;
            if(argument_body())
            {
                if(arr[countt].clasPart=="Round Bracket Close")
                {
                    if(pl==noAtt || pl==0)
                    {
                       insertCDT(n,"","");
                        pl=0;
                    }
                    else
                    {
                       cout<<"no of attributes doesn't match with arguments"<<endl;
                    }
                    countt++;
                    if(arr[countt].clasPart=="Open Curly Bracket")
                    {
                        countt++;
                        if(MST())
                        {
                            destroy();
                            if(arr[countt].clasPart=="Close Curly Bracket")
                            {
                                countt++;
                                return true;
                            }
                        }
                    }

                }
            }
        }
        }
    }
    return false;
}
*/
bool constructor_access_modifier_dec(string am,string t1)
{
    if(arr[countt].clasPart=="id" || arr[countt].clasPart=="var" || arr[countt].clasPart=="func" || arr[countt].clasPart=="secure" || arr[countt].clasPart=="local" || arr[countt].clasPart=="protected")
    {
        /*
    if(constructor(t1,am))
    {
        clas=0;
        return true;
    }
    */
    else if(dec(am))
    {
        return true;
    }
    else if(access_modifiers(am,t1))
    {
        return true;
    }
    }
    return false;
}

bool class_body(string am,string t1)
{
    if(arr[countt].clasPart=="id" || arr[countt].clasPart=="var" || arr[countt].clasPart=="func" || arr[countt].clasPart=="secure" || arr[countt].clasPart=="local" || arr[countt].clasPart=="protected")
 {
     clas =-1;

  if(constructor_access_modifier_dec(t1,am))
  {
      string n=t1;
      if(class_body(am,t1))
      {
          return true;
      }
  }
 }
  else if(arr[countt].clasPart=="Close Curly Bracket")
  {
      currClass="";
      return true;
  }
  return false;
}

bool loop_if()
{
    if(arr[countt].clasPart=="loop_if")
    {
  if(arr[countt].clasPart=="loop_if")
  {
      countt++;
      if(arr[countt].clasPart=="Round Bracket Open")
      {
          countt++;
          if(cond())
          {
              if(arr[countt].clasPart=="Round Bracket Close")
              {
                  countt++;
                  if(loop_if_body())
                  {
                      return true;
                  }
              }
          }
      }
  }
  }
  return false;
}

bool loop_while()
{
    if(arr[countt].clasPart=="loop_while")
    {
    if(arr[countt].clasPart=="loop_while")
    {
        countt++;
            if(arr[countt].clasPart=="Round Bracket Open")
            {
                countt++;
                if(cond())
                {
                    if(arr[countt].clasPart=="Round Bracket Close")
                    {
                        countt++;
                        if(loop_body())
                        {
                            return true;
                        }
                    }
                }
            }
    }
    }
    return false;
}

bool loop_for()
{
    if(arr[countt].clasPart=="loop_for")
    {
   if(arr[countt].clasPart=="loop_for")
   {
       countt++;
       if(arr[countt].clasPart=="Round Bracket Open")
       {
           countt++;
           if(c1())
           {
              if(c2())
                   {
                     if(c3())
                     {
                       if(arr[countt].clasPart=="Round Bracket Close")
                          {
                              countt++;
                              if(loop_body())
                                {
                                    return true;
                                }
                          }
                   }
                }
           }
       }
   }
    }
   return false;
}

bool class_pointer(string am)
{
    if(currClass!="")
    {
    if(arr[countt].clasPart=="this")
    {
    if(arr[countt].clasPart=="this")
    {
        countt++;
        if(arr[countt].clasPart=="->")
        {
            countt++;

            if(arr[countt].clasPart=="id")
            {
                string n=arr[countt].valuePart;
                string t = lookupCDT(n,am);
                if(t=="none")
                {

                    t=lookupParent(n);
                    if(t=="none" || t=="")
                    {
                    cout<<"object not declared or no inheritance"<<endl;
                    }
                    else
                    {
                        string t1= lookupDT(t);
                        if(t1=="none")
                        {
                            cout<<"no class"<<endl;
                        }
                        else if(t1!="class")
                        {
                            cout<<"wrong type for inheritance"<<endl;
                        }
                        else
                        {
                            t1=lookupCDT(t,am);
                            if(t1=="none")
                            {
                                cout<<"object not declared in parent"<<endl;
                            }
                            if(am=="secure")
                            {
                                cout<<"cannot access secure objects"<<endl;
                            }
                        }
                    }
                }
                 else if(t!="var")
                {
                    cout<<"cannot access composite objects"<<endl;
                }
                countt++;
                if(arr[countt].clasPart=="as_op")
                {
                    countt++;
                    if(oe())
                    {

                        return true;
                    }
                }
            }
        }
    }
    }
    }
    else
    {
        cout<<"cannot use outside class"<<endl;
        return true;
    }
    return false;

}


bool obj_to_obj(string am,string n)
{

    if(arr[countt].clasPart=="->")
    {
    if(arr[countt].clasPart=="->")
    {
        countt++;
        if(non_terminal(am,n))
        {
            return true;
        }
    }
    }
    else if(arr[countt].clasPart=="Close Curly Bracket" || arr[countt].clasPart=="var" || arr[countt].clasPart=="func" || arr[countt].clasPart=="loop_if" || arr[countt].clasPart=="loop_for" || arr[countt].clasPart=="loop_while" || arr[countt].clasPart=="this" || arr[countt].clasPart=="id" || arr[countt].clasPart==";")
    {
        return true;
    }

    return false;

}

bool same_ids(string am)
{
    if(arr[countt].clasPart=="id")
    {
    if(arr[countt].clasPart=="id")
    {
        string n=arr[countt].valuePart;
        countt++;
        if(possibilities(am,n))
        {
            return true;
        }

    }
    }
    return false;

}

bool possibilities_5(string am,string t)
{
    if(arr[countt].clasPart=="id" ||arr[countt].clasPart=="func")
    {
    if(array_dec(am,t))
    {
        return true;
    }
    else if(arr[countt].clasPart=="func")
    {
        countt++;
        if(arr[countt].clasPart=="id")
        {
            countt++;
            if(arr[countt].clasPart=="Round Bracket Open")
            {
                countt++;
                if(argument_body())
                {
                    if(arr[countt].clasPart=="Round Bracket Close")
                    {
                        countt++;
                        if(func_body())
                        {
                            return true;
                        }
                    }
                }
            }
        }
    }
    }
    return false;

}

bool argument_body()
{
    if(arr[countt].clasPart=="var")
    {
    if(arr[countt].clasPart=="var")
    {
        countt++;
        if(arr[countt].clasPart=="id")
        {
            countt++;
            pl++;
            if(aglist())
            {
                return true;
            }
        }
    }
    }
    else if(arr[countt].clasPart=="Round Bracket Close")
    {
        return true;
    }
    return false;
}

bool aglist()
{
    if(arr[countt].clasPart=="comma" || arr[countt].clasPart=="Open Square Bracket")
    {
    if(arr[countt].clasPart=="comma")
    {
        countt++;
        if(argument_body())
        {
            return true;
        }

    }
    else if(arraysize())
    {
        if(aglist())
        {
            return true;
        }

    }
    }
    else if(arr[countt].clasPart=="Round Bracket Close")
    {
        return true;
    }
    return false;
}

bool func_body()
{
    if(arr[countt].clasPart=="Open Curly Bracket")
    {
    if(arr[countt].clasPart=="Open Curly Bracket")
    {
        countt++;
        if(MST())
        {
            if(arr[countt].clasPart=="Close Curly Bracket")
            {
                countt++;
                return true;
            }
        }
    }
    }
    return false;
}

bool modifiers(string am)
{
    if(arr[countt].clasPart=="secure" || arr[countt].clasPart=="local" || arr[countt].clasPart=="protected")
    {
        am=arr[countt].clasPart;
    if(arr[countt].clasPart=="secure")
    {
        countt++;
        return true;
    }
    else if(arr[countt].clasPart=="local")
    {
        countt++;
        return true;
    }
    else if(arr[countt].clasPart=="protected")
    {
        countt++;
        return true;
    }
    }
    return false;
}


bool obj_list(string am,string n)
{
    if(arr[countt].clasPart=="comma")
    {
        countt++;
         if(arr[countt].clasPart=="id")
         {
             string n1=arr[countt].valuePart;
             if(!insertCDT(n1,n,am))
             {
                 cout<<"redeclaration error"<<endl;
             }
             countt++;
             if(obj_list(am,n))
             {
                 return true;
             }
         }
    }
    else if(arr[countt].clasPart==";")
        {
            return true;
        }
}

bool constructor_obj(string am, string n)
{
     if(arr[countt].clasPart=="id" || arr[countt].clasPart=="Round Bracket Open")
         {
     if(arr[countt].clasPart=="id")
         {
             string n1=arr[countt].valuePart;
             string t=lookupDT(n);
             if(t=="")
             {
                 cout<<"undeclared"<<endl;
             }
             else if(t!="class")
             {
                 cout<<"undeclared class"<<endl;
             }
             else if(!insertCDT(n1,n,am))
             {
                 cout<<"redeclaration error"<<endl;
             }
             countt++;
             if(obj_list(am,n))
             {
            if(arr[countt].clasPart==";")
            {
                countt++;
                if(obj_dec(am))
                {
                return true;
                }
            }
         }
         }
    else  if(arr[countt].clasPart=="Round Bracket Open")
        {
            clas=0;
        if(n!=currClass)
        {
            cout<<"wrong type for constructor"<<endl;
        }
         createScope();
            countt++;
            if(argument_body())
            {
                if(arr[countt].clasPart=="Round Bracket Close")
                {
                     if(pl==noAtt || pl==0)
                    {
                       if(!insertCDT(n,"",am))
                       {
                           cout<<"redeclaration error"<<endl;
                       }
                        pl=0;
                    }
                    else
                    {
                       cout<<"no of attributes doesn't match with arguments"<<endl;
                    }
                    countt++;
                    if(arr[countt].clasPart=="Open Curly Bracket")
                    {
                        countt++;
                        if(MST())
                        {
                            if(arr[countt].clasPart=="Close Curly Bracket")
                            {
                                 destroy();
                                countt++;
                                clas=-1;
                                return true;
                            }
                        }
                    }

                }
            }
        }
         }
 return false;
}

bool obj_dec(string am)
{
    clas=-1;
    if(arr[countt].clasPart=="id" || arr[countt].clasPart=="var")
    {
    if(arr[countt].clasPart=="id")
    {
        string n=arr[countt].valuePart;
        countt++;
         if(constructor_obj(am,n))
         {
             return true;
         }
    }

    else if(dec(am))
    {

        if(obj_dec(am))
        {
            return true;
        }
    }
   }
    else  if(arr[countt].clasPart=="local" || arr[countt].clasPart=="secure" || arr[countt].clasPart=="protected" ||  arr[countt].clasPart=="var")
   {
       return true;
   }
   else if(arr[countt].clasPart=="Curly Bracket Close")
   {
       clas=0;
       return true;
   }
  return false;
}

bool access_modifiers(string am)
{
    if(arr[countt].clasPart=="secure" || arr[countt].clasPart=="local" || arr[countt].clasPart=="protected")
    {
    if(modifiers(am))
    {
        if(arr[countt].clasPart=="colon")
        {
            countt++;
            if(obj_dec(am))
            {
                return true;
            }
        }
    }
    }
    return false;
}

/*
bool access_modifiers(string am,string t1)
{
    if(arr[countt].clasPart=="secure" || arr[countt].clasPart=="local" || arr[countt].clasPart=="protected")
    {
    if(modifiers(am))
    {
        if(arr[countt].clasPart=="colon")
        {
            countt++;
            if(dec(am))
            {
                return true;
            }
        }
    }
    }
    return false;
}
*/
bool cond()
{
    if(arr[countt].clasPart=="var" || arr[countt].clasPart=="func" || arr[countt].clasPart=="!" || arr[countt].clasPart=="id" || arr[countt].clasPart=="int" || arr[countt].clasPart=="float" || arr[countt].clasPart=="string")
    {


 if(oe())
 {
     return true;
 }

    }
 return false;
}

bool loop_if_body()
{
    if(arr[countt].clasPart=="Open Curly Bracket")
    {

 if(arr[countt].clasPart=="Open Curly Bracket")
 {
     countt++;
     if(MST())
     {
         if(arr[countt].clasPart=="Close Curly Bracket")
         {
             countt++;
             if(loop_else_if())
             {
                 return true;
             }
         }
     }
 }
    }
 return false;
}

bool loop_else_if()
{
    if(arr[countt].clasPart=="loop_else_if" || arr[countt].clasPart=="else")
    {
    if(loop())
    {
        if(arr[countt].clasPart=="Open Curly Bracket")
        {
            countt++;
            if(MST())
            {
                if(arr[countt].clasPart=="Close Curly Bracket")
                {
                    countt++;
                    return true;
                }
            }
        }
    }
    }
    else if(arr[countt].clasPart=="Close Curly Bracket" || arr[countt].clasPart=="var" || arr[countt].clasPart=="func" || arr[countt].clasPart=="loop_if" || arr[countt].clasPart=="loop_for" || arr[countt].clasPart=="loop_while" || arr[countt].clasPart=="this" || arr[countt].clasPart=="id" || arr[countt].clasPart==";")
    {
      return true;
    }
    return false;
}

bool loop()
{
    if(arr[countt].clasPart=="loop_else_if" || arr[countt].clasPart=="loop_else")
    {
    if(loops())
    {
        if(arr[countt].clasPart=="Round Bracket Open")
        {
            countt++;
            if(cond())
            {
                if(arr[countt].clasPart=="Round Bracket Close")
                {
                    countt++;
                    return true;
                }
            }
        }
    }
    }
    return false;

}

bool loops()
{
    if(arr[countt].clasPart=="loop_else_if" || arr[countt].clasPart=="loop_else")
    {
    if(arr[countt].clasPart=="loop_else_if")
    {
        countt++;
        return true;
    }
    else if(arr[countt].clasPart=="loop_else")
    {
      countt++;
      return true;
    }
    }
    return false;
}

bool loop_body()
{
    if(arr[countt].clasPart=="Open Curly Bracket")
    {
    if(arr[countt].clasPart=="Open Curly Bracket")
    {
        countt++;
        if(MST())
        {
            if(arr[countt].clasPart=="Close Curly Bracket")
            {
                countt++;
                cout<<arr[countt].clasPart<<endl;
                return true;
            }
        }
    }
    }
    return false;
}

bool c1()
{
    if(arr[countt].clasPart=="var" || arr[countt].clasPart==";")
    {
    if(arr[countt].clasPart=="var")
    {
       countt++;
       if(arr[countt].clasPart=="id")
       {
           countt++;
           if(arr[countt].clasPart=="as_op")
           {
               countt++;
            if(oe())
            {
                if(arr[countt].clasPart==";")
                {
                 countt++;
                return true;
                }
            }
           }
       }
    }
    else if(arr[countt].clasPart==";")
    {
        countt++;
        return true;
    }
    }
    return false;
}

bool c2()
{
     if(arr[countt].clasPart=="var" || arr[countt].clasPart=="func" || arr[countt].clasPart=="!" || arr[countt].clasPart=="id" || arr[countt].clasPart=="int" || arr[countt].clasPart=="float" || arr[countt].clasPart=="string" || arr[countt].clasPart==";")
    {
    if(oe_n())
    {
        if(arr[countt].clasPart==";")
        {
            countt++;
            return true;
        }
    }
    }
    return false;
}

bool oe_n()
{

    if(oe())
    {
        return true;
    }
    else if(arr[countt].clasPart==";")
    {
        return true;
    }
    return false;
}

bool c3()
{
    if(arr[countt].clasPart=="id")
    {
   if(arr[countt].clasPart=="id")
   {
   countt++;
   if(inc_dec_op())
   {
       return true;
   }
   }
    }
    else if(arr[countt].clasPart=="Round Bracket Close")
    {
        return true;
    }
    return false;
}

bool non_terminal2(string am,string n)
{
    if(arr[countt].clasPart=="id")
    {
        if(arr[countt].clasPart=="id")
        {
            string n1=arr[countt].valuePart;
            t=lookupST(n);
            if(t=="none")
            {
                cout<<"object not declared"<<endl;
            }
            else if(t!="class")
            {
                cout<<"object is not class type"<<endl;
            }
            else
            {
                lookupCDT(n1,am)
            }
            countt++;
            if(in_func_call())
            {
                return true;
            }
        }
    }
    return false;
}

bool in_func_call()
{

    if(arr[countt].clasPart=="as_op" || arr[countt].clasPart=="->" || arr[countt].clasPart=="Round Bracket Open" || arr[countt].clasPart==";")
    {
        if(init())
        {
          return true;
        }
    else if(arr[countt].clasPart=="Round Bracket Open")
    {
        countt++;
        if(function_parameter())
        {
            if(arr[countt].clasPart=="Round Bracket Close")
            {
                countt++;
                return true;
            }
        }
    }
    }
    return false;
}

bool non_terminal(string am,string n)
{
    if(arr[countt].clasPart=="id" || arr[countt].clasPart=="Round Bracket Open")
    {
   if(non_terminal2(am,n))
   {
       if(obj_to_obj(am,n))
       {
           return true;
       }
   }
    }
    return false;

}

bool func_call()
{
    if(arr[countt].clasPart=="id")
    {
    if(arr[countt].clasPart=="id")
    {
        countt++;
    if(arr[countt].clasPart=="Round Bracket Open")
    {
        countt++;
        if(function_parameter())
        {
            if(arr[countt].clasPart=="Round Bracket Close")
            {
                countt++;
                return true;
            }
        }
    }
    }
    }
    return false;
}

bool class_obj_dec()
{
    if(arr[countt].clasPart=="id")
    {
    if(arr[countt].clasPart=="id")
    {
        countt++;
        if(id_nt())
        {
            return true;
        }
    }
    }
    return false;
}

bool id_nt()
{
    if(arr[countt].clasPart=="loop_if" || arr[countt].clasPart=="var"||arr[countt].clasPart=="loop_while" || arr[countt].clasPart=="this" || arr[countt].clasPart=="id" || arr[countt].clasPart==";" || arr[countt].clasPart=="func" || arr[countt].clasPart=="loop_for" || arr[countt].clasPart=="}")
    {

    if(class_obj_para_func_call())
    {
        return true;
    }
    }
    else if(arr[countt].clasPart=="Close Curly Bracket" || arr[countt].clasPart=="var" || arr[countt].clasPart=="func" || arr[countt].clasPart=="loop_if" || arr[countt].clasPart=="loop_for" || arr[countt].clasPart=="loop_while" || arr[countt].clasPart=="this" || arr[countt].clasPart=="id" || arr[countt].clasPart==";")
    {
        return true;
    }

   return false;
}

bool possibilities(string am, string n)
{
    if(arr[countt].clasPart=="Round Bracket Open" || arr[countt].clasPart=="++" || arr[countt].clasPart=="--" || arr[countt].clasPart=="id" || arr[countt].clasPart=="->")
    {
    if(class_obj_para_func_call(am,n))
    {
        return true;

    }
    else if(inc_dec_op(am,n))
    {
        return true;

    }
    else if(class_obj_dec(am,n))
    {
     return true;
    }
    else if(obj_to_obj(am,n))
    {
        return true;

    }
    }

    return false;

}

bool class_obj_para_func_call(string am,string n)
{
    if(arr[countt].clasPart=="Round Bracket Open")
    {
    if(arr[countt].clasPart=="Round Bracket Open")
    {

        countt++;
        if(function_parameter())
        {
            if(arr[countt].clasPart=="Round Bracket Close")
            {
                countt++;
        if(currClass!="")
        {
            string t = lookupST(n);
            if(t=="none")
            {
                t=lookupCDT(n,am);
                if(t="none")
                {
                    cout<<"object not declared"<<endl;
                }
            }
             if(t=="var")
                {
                    cout<<"error its a var"<<endl;
                }
              else
                {
                    string t1=lookupDT(t);
                    if(t1=="none")
                    {
                        cout<<"undeclared"<<endl;
                    }
                    else if(t1!="class")
                    {
                        cout<<"undeclared class"<<endl;
                    }/*
                    else
                    {
                      t1=lookupCDT()
                    }*/
                }
                string t = lookupDTFN(n,pl);
                if(t=="none")
                {
                    cout<<"no function declaration"<<endl;
                }


        }
            return true;
            }
        }
    }
    }
    return false;

}

bool inc_dec_op(string am, string n)
{
    if(arr[countt].clasPart=="++" || arr[countt].clasPart=="--")
    {
    if(arr[countt].clasPart=="++")
    {
        if(currClass!="")
        {
            string t = lookupCDT(n,am);
                if(t=="none")
                {
                    t=lookupParent(n);
                    if(t=="none" || t=="")
                    {
                    cout<<"object not declared or no inheritance"<<endl;
                    }
                    else
                    {
                        string t1= lookupDT(t);
                        if(t1=="none")
                        {
                            cout<<"no class"<<endl;
                        }
                        else if(t1!="class")
                        {
                            cout<<"wrong type for inheritance"<<endl;
                        }
                        else
                        {
                            t1=lookupCDT(t,am);
                            if(t1=="none")
                            {
                                cout<<"object not declared in parent"<<endl;
                            }
                            if(am=="secure")
                            {
                                cout<<"cannot access secure objects"<<endl;
                            }
                        }
                    }
                }
                else if(t!="var")
                {
                    cout<<"cannot increment composite objects"<<endl;
                }
        }
        else
        {
            string t = lookupST(n);
            if(t=="none")
            {
                cout<<"not declared"<<endl;
            }
            else if(t!=var)
            {
                cout<<"cannot increment that are not var objects"<<endl;
            }
        }
        countt++;
        return true;
    }
    else if(arr[countt].clasPart=="--")
            {
                if(currClass!="")
              {
            string t = lookupCDT(n,am);
                if(t=="none")
                {
                    t=lookupParent(n);
                    if(t=="none" || t=="")
                    {
                    cout<<"object not declared or no inheritance"<<endl;
                    }
                    else
                    {
                        string t1= lookupDT(t);
                        if(t1=="none")
                        {
                            cout<<"no class"<<endl;
                        }
                        else if(t1!="class")
                        {
                            cout<<"wrong type for inheritance"<<endl;
                        }
                        else
                        {
                            t1=lookupCDT(t,am);
                            if(t1=="none")
                            {
                                cout<<"object not declared in parent"<<endl;
                            }
                            if(am=="secure")
                            {
                                cout<<"cannot access secure objects"<<endl;
                            }
                        }
                    }
                }
                else if(t!="var")
                {
                    cout<<"cannot decrement composite objects"<<endl;
                }
        }
        else
        {
            string t = lookupST(n);
            if(t=="none")
            {
                cout<<"not declared"<<endl;
            }
            else if(t!=var)
            {
                cout<<"cannot decrement that are not var objects"<<endl;
            }
        }
             countt++;
              return true;
            }
    }
    return false;

}

bool function_parameter()
{
    if(arr[countt].clasPart=="var" || arr[countt].clasPart=="func" || arr[countt].clasPart=="!" || arr[countt].clasPart=="id" || arr[countt].clasPart=="int" || arr[countt].clasPart=="float" || arr[countt].clasPart=="string")
    {

    if(oe())
    {
        pl++;
       if(func_paralist())
       {
           return true;
       }
    }
    }
    else if(arr[countt].clasPart=="Round Bracket Close")
    {

        return true;
    }
    return false;

}

bool func_paralist()
{
    if(arr[countt].clasPart=="comma")
    {
    if(arr[countt].clasPart=="comma")
    {
        if(function_parameter())
        {
            return true;
        }
    }
    }
    else if(arr[countt].clasPart=="Round Bracket Close" ||  arr[countt].clasPart=="var" || arr[countt].clasPart=="func" || arr[countt].clasPart=="!" || arr[countt].clasPart=="id" || arr[countt].clasPart=="int" || arr[countt].clasPart=="float" || arr[countt].clasPart=="string")
    {

        return true;
    }
    return false;
}

bool array_dec(string am,string t)
{
    if(arr[countt].clasPart=="id")
    {
    if(arr[countt].clasPart=="id")
    {
        string n=arr[countt].valuePart;
        countt++;
        if(possibilities_4(am,n,t))
        {
            return true;
        }
    }
    }
    return false;
}

bool possibilities_4(string am, string n, string t)
{
    if(arr[countt].clasPart=="as_op" || arr[countt].clasPart=="Open Square Bracket" || arr[countt].clasPart=="comma" || arr[countt].clasPart==";")
    {

    if(init())
    {
        if(Clas==-1)
        {
            if(am=="")
            {
                am="private";
            }
            if(!insertCDT(n,"",am))
            {
                cout<<"redecleration error"<<endl;
            }
            else
            {
                noAtt++;
            }
        }
        else if(!insertST(n,t,s))
        {
            cout<<"redecleration error"<<endl;
        }
        if(list(am,n,t))
        {
            return true;
        }
    }
    else if(array_possibilities(am,n,t))
    {
        return true;
    }
    }
    return false;
}

bool list(string n, string t)
{
    if(arr[countt].clasPart=="comma" || arr[countt].clasPart==";")
    {
    if(arr[countt].clasPart=="comma")
    {
        countt++;
        if(arr[countt].clasPart=="id")
        {
             n=arr[countt].valuePart;
            countt++;
            if(possibilities_4(n,t))
            {
                return true;
            }
        }
    }
    else if(arr[countt].clasPart==";")
    {
        countt++;
        return true;

    }
    }
    return false;

}

bool init()
{
    if(arr[countt].clasPart=="as_op")
    {
    if(arr[countt].clasPart=="as_op")
    {
        countt++;
        if(list2())
        {
            return true;
        }
    }
    }
    else if(arr[countt].clasPart=="comma" || arr[countt].clasPart=="->" || arr[countt].clasPart==";" || arr[countt].clasPart=="var" || arr[countt].clasPart=="func" || arr[countt].clasPart=="loop_if" || arr[countt].clasPart=="loop_while" || arr[countt].clasPart=="loop_for" || arr[countt].clasPart=="this" || arr[countt].clasPart=="id" || arr[countt].clasPart=="Close Curly Bracket")
    {
        return true;

    }

    return false;

}

bool array_possibilities(string am,string n,string t)
{
    if(arr[countt].clasPart=="Open Square Bracket")
    {
    if(arraysize())
    {
        if(possibilities_3(am,n,t))
        {
            return true;
        }
    }
    }
    return false;
}

bool list2()
{

if(arr[countt].clasPart=="var" || arr[countt].clasPart=="func" || arr[countt].clasPart=="!" || arr[countt].clasPart=="id" || arr[countt].clasPart=="float" || arr[countt].clasPart=="string" || arr[countt].clasPart=="int_const")
{


    if(oe())
    {
        return true;
    }
}
    return false;
}

bool arraysize()
{
    if(arr[countt].clasPart=="Open Square Bracket")
    {

    if(arr[countt].clasPart=="Open Square Bracket")
    {
        countt++;
        if(oe())
        {
            if(arr[countt].clasPart=="Close Square Bracket")
            {
                countt++;
                check++;
                if(arraysize_2d())
                {
                    return true;

                }
            }
        }
    }
    }
    return false;
}

bool arraysize_2d()
{
    if(arr[countt].clasPart=="Open Square Bracket")
    {
    if(arr[countt].clasPart=="Open Square Bracket")
       {
           countt++;
           if(oe())
            {
              if(arr[countt].clasPart=="Close Square Bracket")
              {
                  countt++;
                  check++;
                  return true;
              }
            }
       }
    }
       else if(arr[countt].clasPart=="comma" || arr[countt].clasPart=="as_op" || arr[countt].clasPart=="Round Bracket Close" || arr[countt].clasPart=="MDM" || arr[countt].clasPart=="PM" || arr[countt].clasPart=="Relational Op" || arr[countt].clasPart=="and" || arr[countt].clasPart=="or" ||arr[countt].clasPart=="comma" || arr[countt].clasPart==";" || arr[countt].clasPart=="Close Square Bracket" || arr[countt].clasPart=="Round Bracket Close" || arr[countt].clasPart=="Close Curly Bracket")

       {
           check=0;
           return true;
       }
       return false;
}

bool possibilities_3(string am,string n,string t)
{
    if(arr[countt].clasPart=="comma" || arr[countt].clasPart=="as_op" || arr[countt].clasPart==";")
    {

  if(left(am,n,t))
  {
      return true;
  }
  else if(arr[countt].clasPart=="as_op")
  {
      countt++;
      if(array_body(am,n,t))
      {
        return true;
      }
    }
    else if(arr[countt].clasPart==";")
    {
         if(Clas==-1)
        {
            if(am=="")
            {
                am="private";
            }
            if(!insertCDT(n,"",am))
            {
                cout<<"redecleration error"<<endl;
            }
            else
            {
                noAtt++;
            }
        }
        else if(!insertST(n,t,s))
        {
            cout<<"redecleration error"<<endl;
        }
        countt++;
        return true;
    }
    }
    return false;
}

bool left(string am,string n,string t)
{
    if(arr[countt].clasPart=="comma")
    {
    if(arr[countt].clasPart=="comma")
    {
        countt++;
        if(arr[countt].clasPart=="id")
        {
            n=arr[countt].valuePart;
            countt++;
            if(array_and_list(am,n,t))
            {
                return true;
            }
        }
    }
    }
    return false;
}

bool array_body(string am,string n, string t)
{
    if(arr[countt].clasPart=="Open Curly Bracket")
    {
    if(arr[countt].clasPart=="Open Curly Bracket")
    {
        countt++;
        if(array_list2())
        {
            if(arr[countt].clasPart=="Close Curly Bracket")
            {
               countt++;


               if(array_list4())
                    {
                        if(arr[countt].clasPart==";")
                        {
                              if(Clas==-1)
        {
            if(am=="")
            {
                am="private";
            }
            if(!insertCDT(n,"",am))
            {
                cout<<"redecleration error"<<endl;
            }
            else
            {
                noAtt++;
            }
        }
        else if(!insertST(n,t,s))
        {
            cout<<"redecleration error"<<endl;
        }
                            countt++;

                        return true;
                        }
                    }
            }
        }
    }
    }


    return false;
}

bool array_list4()
{
  if(arr[countt].clasPart=="comma")
  {

    if(arr[countt].clasPart=="comma")
    {
        countt++;
        if(arr[countt].clasPart=="Open Curly Bracket")
        {
            countt++;
            if(array_list2())
            {
                if(arr[countt].clasPart=="Close Curly Bracket")
                {
                    countt++;
                    check=0;
                    return true;
                }
            }
        }
    }
  }
   else if(arr[countt].clasPart==";")
    {


        return true;
    }
    check=0;
    return false;
}

bool array_list3()
{
    if(arr[countt].clasPart=="comma")
    {
   if(arr[countt].clasPart=="comma")
   {
       countt++;
       if(array_list2())
       {
           return true;
       }
   }
    }
   else if(arr[countt].clasPart=="Close Curly Bracket")
   {
       return true;
   }
   return false;
}

bool array_list2()
{
    if(arr[countt].clasPart=="var" || arr[countt].clasPart=="func" || arr[countt].clasPart=="!" || arr[countt].clasPart=="id" || arr[countt].clasPart=="int_const" || arr[countt].clasPart=="float" || arr[countt].clasPart=="string")
    {

    if(oe())
    {
        if(array_list3())
        {
            return true;
        }

    }
    }
    return false;
}

bool array_and_list(string am,string n,string t)
{
    if(arr[countt].clasPart=="as_op" || arr[countt].clasPart=="comma" || arr[countt].clasPart=="->" || arr[countt].clasPart=="Open Square Bracket" || arr[countt].clasPart=="Round Bracket Open")
    {
    if(list_work(am,n,t))
    {
        return true;
    }
    else if(array_list_work(am,n,t))
    {
        return true;
    }
    }
    return false;
}

bool list_work(string am,string n,string t)
{
    if(arr[countt].clasPart=="as_op" || arr[countt].clasPart=="as_op" || arr[countt].clasPart=="comma" || arr[countt].clasPart=="->"|| arr[countt].clasPart=="Round Bracket Open")
   {
    if(init())
    {
        if(list(am,n,t))
        {
             if(Clas==-1)
        {
            if(am=="")
            {
                am="private";
            }
            if(!insertCDT(n,"",am))
            {
                cout<<"redecleration error"<<endl;
            }
            else
            {
                noAtt++;
            }
        }
        else if(!insertST(n,t,s))
        {
            cout<<"redecleration error"<<endl;
        }
            return true;
        }
    }
   }
    return false;
}

bool array_list_work(string am,string n,string t)
{
    if(arr[countt].clasPart=="Open Square Bracket")
    {
    if(arraysize())
    {
         if(Clas==-1)
        {
            if(am=="")
            {
                am="private";
            }
            if(!insertCDT(n,"",am))
            {
                cout<<"redecleration error"<<endl;
            }
            else
            {
                noAtt++;
            }
        }
        else if(!insertST(n,t,s))
        {
            cout<<"redecleration error"<<endl;
        }
        return true;
    }
    }
    return false;
}

bool thiss_oe()
{
     if(arr[countt].clasPart=="this" || arr[countt].clasPart=="var" || arr[countt].clasPart=="func" || arr[countt].clasPart=="!" || arr[countt].clasPart=="id" || arr[countt].clasPart=="int_const" || arr[countt].clasPart=="float_const" || arr[countt].clasPart=="string")
  {
    if(arr[countt].clasPart=="this")
    {
        countt++;
        if(arr[countt].clasPart=="->")
           {
               countt++;
               if(oe())
                {
                    return true;
                }
           }
    }
    else if(oe())
    {
        return true;
    }
  }
  return false;
}

bool ret()
{
    if(arr[countt].clasPart=="ret")
    {
    if(arr[countt].clasPart=="ret")
    {
        countt++;
        if(thiss_oe())
        {
            return true;
        }
    }
    }
    return false;
}

bool oe()
{

  if(arr[countt].clasPart=="var" || arr[countt].clasPart=="func" || arr[countt].clasPart=="!" || arr[countt].clasPart=="id" || arr[countt].clasPart=="int_const" || arr[countt].clasPart=="float_const" || arr[countt].clasPart=="string")
  {
  if(ae())

  {
      if(oe_())
      {
          return true;
      }
  }
  }
  return false;
}
bool ae()
{
    if(arr[countt].clasPart=="var" || arr[countt].clasPart=="func" || arr[countt].clasPart=="!" || arr[countt].clasPart=="id" || arr[countt].clasPart=="int_const" || arr[countt].clasPart=="float_const" || arr[countt].clasPart=="string")
  {
    if(rope())
    {
        if(ae_())
        {
            return true;
        }
    }
  }
    return false;
}
bool oe_()
{
    if(arr[countt].clasPart=="or")
    {

    if(arr[countt].clasPart=="or")
    {
        countt++;
        if(ae())
        {
            if(oe_())
            {
                return true;
            }
        }
    }
    }
    else if(arr[countt].clasPart=="comma")
    {

        return true;
    }
    else if(arr[countt].clasPart=="Round Bracket Close")
    {

        return true;
    }
    else if(arr[countt].clasPart==";")
    {

        return true;
    }
    else if(arr[countt].clasPart=="Close Square Bracket" || arr[countt].clasPart=="Close Curly Bracket")
    {

        return true;
    }
    return false;
}
bool ae_()
{
    if(arr[countt].clasPart=="and")
    {
    if(arr[countt].clasPart=="and")
    {
        countt++;
        if(rope())
        {
            if(ae_())
            {
                return true;
            }
        }
    }
    }
    else if(arr[countt].clasPart=="Close Curly Bracket" || arr[countt].clasPart=="or" || arr[countt].clasPart=="comma" || arr[countt].clasPart==";" || arr[countt].clasPart=="Close Square Bracket" || arr[countt].clasPart=="Round Bracket Close")
    {
        return true;
    }
    return false;
}
bool rope()
{
     if(arr[countt].clasPart=="var" || arr[countt].clasPart=="func" || arr[countt].clasPart=="!" || arr[countt].clasPart=="id" || arr[countt].clasPart=="int_const" || arr[countt].clasPart=="float_const" || arr[countt].clasPart=="string")
  {
    if(e())
    {
        if(rope_())
        {
            return true;
        }
    }
  }
    return false;
}
bool rope_()
{
     if(arr[countt].clasPart=="Relational Op")
     {
    if(arr[countt].clasPart=="Relational Op")
    {
        countt++;
        if(e())
        {
            if(rope_())
            {
                return true;
            }
        }
    }
     }
    else if(arr[countt].clasPart=="Close Curly Bracket" || arr[countt].clasPart=="and" || arr[countt].clasPart=="or" || arr[countt].clasPart=="comma" || arr[countt].clasPart==";" || arr[countt].clasPart=="Close Square Bracket" || arr[countt].clasPart=="Round Bracket Close")
    {
        return true;
    }
    return false;
}
bool e()
{
    if(arr[countt].clasPart=="var" || arr[countt].clasPart=="func" || arr[countt].clasPart=="!" || arr[countt].clasPart=="id" || arr[countt].clasPart=="int_const" || arr[countt].clasPart=="float_const" || arr[countt].clasPart=="string")
  {
    if(t())
    {
        if(e_())
        {
            return true;
        }
    }
  }
    return false;
}
bool t()
{
    if(arr[countt].clasPart=="var" || arr[countt].clasPart=="func" || arr[countt].clasPart=="!" || arr[countt].clasPart=="id" || arr[countt].clasPart=="int_const" || arr[countt].clasPart=="float_const" || arr[countt].clasPart=="string")
  {
   if(f())
   {
       if(t_())
       {
           return true;
       }
   }
  }
   return false;
}
bool t_()
{
    if(arr[countt].clasPart=="MDM")
    {
    if(arr[countt].clasPart=="MDM")
    {
        countt++;
        if(f())
        {
            if(t_())
            {
                return true;
            }
        }
    }
    }
    else if(arr[countt].clasPart=="PM" || arr[countt].clasPart=="Relational Op" || arr[countt].clasPart=="and" || arr[countt].clasPart=="or" ||arr[countt].clasPart=="comma" || arr[countt].clasPart==";" || arr[countt].clasPart=="Close Square Bracket" || arr[countt].clasPart=="Round Bracket Close" || arr[countt].clasPart=="Close Curly Bracket")
    {
        return true;
    }
    return false;
}
bool f()
{
     if(arr[countt].clasPart=="var" || arr[countt].clasPart=="func" || arr[countt].clasPart=="!" || arr[countt].clasPart=="id" || arr[countt].clasPart=="int_const" || arr[countt].clasPart=="float_const" || arr[countt].clasPart=="string")
  {

    if(sameids2() || uop() || dec())
    {
        return true;
    }
    else if(arr[countt].clasPart=="int_const" || arr[countt].clasPart=="float_const" || arr[countt].clasPart=="string")
    {
        countt++;
        return true;
    }
  }
    return false;
}

bool sameids2()
{
    if(arr[countt].clasPart=="id")
  {
  if(arr[countt].clasPart=="id")
  {
      string n=arr[countt].valuePart;
      countt++;
      if(possibilities_7(n))
      {
         return true;
      }
  }
  }
  return false;
}

bool uop()
{
     if(arr[countt].clasPart=="!")
    {
    if(arr[countt].clasPart=="!")
    {
        countt++;
        if(id_func())
        {
            return true;
        }
    }
    }
    return false;
}
bool id_func()
{
    if(arr[countt].clasPart=="id")
    {
    if(arr[countt].clasPart=="id")
    {
        countt++;
        if(func_work())
        {
            return true;
        }
    }
    }
    return false;

}
bool func_work()
{
    if(arr[countt].clasPart=="Round Bracket Close")
    {
    if(arr[countt].clasPart=="Round Bracket Close")
    {
        countt++;
        if(function_parameter())
        {
            if(arr[countt].clasPart=="Round Bracket Close")
            {
                countt++;
                return true;
            }
        }
    }
    }
    else if(arr[countt].clasPart=="MDM" || arr[countt].clasPart=="PM" || arr[countt].clasPart=="Relational Op" || arr[countt].clasPart=="and" || arr[countt].clasPart=="or" ||arr[countt].clasPart=="comma" || arr[countt].clasPart==";" || arr[countt].clasPart=="Close Square Bracket" || arr[countt].clasPart=="Round Bracket Close" || arr[countt].clasPart=="Close Curly Bracket")
    {
        return true;
    }
    return false;
}
bool e_()
{
    if(arr[countt].clasPart=="PM")
    {
    if(arr[countt].clasPart=="PM")
    {
        countt++;
        if(t())
        {

            if(e_())
            {
                return true;
            }
        }
    }
    }
    else if(arr[countt].clasPart=="Relational Op" || arr[countt].clasPart=="comma" || arr[countt].clasPart==";" || arr[countt].clasPart=="Close Square Bracket" ||arr[countt].clasPart=="Round Bracket Close" || arr[countt].clasPart=="Close Curly Bracket" ||  arr[countt].clasPart=="and" ||  arr[countt].clasPart=="or")
    {
        return true;
    }
    return false;

}

bool possibilities_7(string n)
{

    if(arr[countt].clasPart=="Open Square Bracket" || arr[countt].clasPart=="Round Bracket Open" || arr[countt].clasPart=="++" || arr[countt].clasPart=="--" || arr[countt].clasPart=="->")
    {

    if(arr[countt].clasPart=="Round Bracket Open")
    {
        pl=0;
        countt++;
         if(function_parameter())
         {
             string t=lookupDTFN(n,pl);
             if(t=="none")
             {
                 cout<<"undeclared function "<<endl;
             }
              if(arr[countt].clasPart=="Round Bracket Close")
              {
                  countt++;
                  return true;
              }
         }
    }
    else if(arraysize())
    {
        return true;
    }
    else if(inc_dec_op())
    {
        return true;
    }
     else if(arr[countt].clasPart=="->")
    {
        countt++;
        if(sameids2())
        {
            return true;
        }

    }
    }
    else if(arr[countt].clasPart=="MDM" || arr[countt].clasPart=="PM" || arr[countt].clasPart=="Relational Op" || arr[countt].clasPart=="and" || arr[countt].clasPart=="or" ||arr[countt].clasPart=="comma" || arr[countt].clasPart==";" || arr[countt].clasPart=="Close Square Bracket" || arr[countt].clasPart=="Round Bracket Close" || arr[countt].clasPart=="Close Curly Bracket")
    {
       return true;
    }
    return false;
}
/*
void semanticAnalyzer()
{

}
*/
 int checker=0;
bool insertST(string n,string t,int s)
{

    if(ST[checker].name == NULL)
    {
        ST[checker].name = n;
        ST[checker].type = t;
        ST[checker].scope = s;
        return true;
    }
    bool chek = lookupST(n,s);
    if(chek == false)
    {
        checker++;
        ST[checker].name = n;
        ST[checker].type = t;
        ST[checker].scope = s;

        return true;
    }
    else
    {
        return false;
    }
}

bool lookupST(string n,int s)
{
    for(int i=0;i<=checker;i++)
    {
        if(ST[checker].name == n && ST[checker].scope == s)
        {
            return true;
        }
    }
    return false;

}

string lookupST(string n)
{
     stack <int> temp=ss;
    while(!temp.empty()){
   for(int i=0;i<=checker;i++)
    {
        if(ST[checker].name == n && ST[checker].scope == temp.top()){
            return ST[checker].type;
        }
    }
    temp.pop();
    }
    return "none";
}

int incre=0;

string lookupDTFN(string n,string p)
{
    for(int i=0;i<=incre;i++)
    {
        if(DT[i].name == n && DT[i].p == pl)
        {
            return DT[i].type;
        }
    }
    return "none";

}

bool insertDTFN(string n,string t,string p)
{
     if(DT[incre].name == NULL)
    {
        DT[incre].name = n;
        DT[incre].type = t;
        DT[incre].parent = p;
        return true;
    }
    bool chek = lookupDTFN(n,p);
    if(chek == "none")
    {
        incre++;
        DT[incre].name = n;
        DT[incre].type = t;
        DT[incre].parent = p;
        return true;
    }
    else
    {
        return false;
    }
}

bool insertDT(string n,string t,string p)
{
    if(DT[incre].name == NULL)
    {
        DT[incre].name = n;
        DT[incre].type = t;
        DT[incre].parent = p;
        return true;
    }

    bool chek = lookupDT(n);
    if(chek == "none")
    {
        incre++;
        DT[incre].name = n;
        DT[incre].type = t;
        DT[incre].parent = p;
        return true;
    }
    else
    {
        return false;
    }
}

string lookupDT(string n)
{
     for(int i=0;i<=incre;i++)
    {
        if(DT[i].name == n )
        {
            return DT[i].type;
        }
    }
    return "none";

}
int inc=0;
int temp=0;
/*
bool lookupCDT(string n)
{
    for(int i=0;i<=incre;i++)
    {
        if(DT[i].name == n )
        {
            temp=i;
            break;
        }
    }
}
*/
bool insertCDT(string n,string t, string accessm)
{

    for(int i=0;i<=incre;i++)
    {
      if(DT[i].name == currClass)
      {
          DT[i].CDT = new dataTable[5];
        temp = i;
        break;
      }
    }
    if(DT[temp].CDT[inc].name == NULL)
    {
        DT[temp].CDT[inc].name = n;
        DT[temp].CDT[inc].type = t;
        DT[temp].CDT[inc].am = accessm;
        return true;
    }
    string am = "";
    bool chek = lookupCDT(n,am);
    if(chek == "none")
    {
        inc++;
        DT[temp].CDT[inc].name = n;
        DT[temp].CDT[inc].type = t;
        DT[temp].CDT[inc].am = accessm;
        return true;
    }
    else
    {
        return false;
    }

}

string lookupParent(string n)
{
  for(int i=0;i<=incre;i++)
    {
        if(DT[i].name == n )
        {
            temp=i;
            return DT[i].parent;
        }
    }
    return "none";
}
/*
string lookupFN(classname,name){
    name = name,
    type = void/var,
    parent = noOfParams

}
*/
string lookupCDT(string n,string & am)
{
     for(int i=0;i<=inc;i++)
    {
        if(DT[temp].CDT[inc].name == n)
        {
            am = DT[temp].CDT[inc].am;
            return DT[temp].CDT[inc].type;
        }
    }
    return "none";

}

bool lookupConstructor(string n, string p)
{
    for(int i=0;i<=inc;i++)
    {

    }
}

void writeInFile(string word) {
   ofstream file_;
   file_.open("token.txt");
   file_ <<word;
   file_<<endl;
   file_.close();
}
int main()
{
    int k=0;
  string data;
  string tosend="";
  ifstream file_("file.txt");
  if(file_.is_open())
  {
      while(getline(file_,data))
      {
          cout<<data<<endl<<endl;
          k+=data.length();
          data+="\\";
          data+="n";
          data+=" ";
          tosend+=data;
      }
      file_.close();
  }
  else
  {
      cout<<"file not open"<<endl;
  }
    int sizee;
    sizee=k;
    temparr = new syntaxCheck[sizee];


    lexicalAnalyzer(tosend);

    temparr[counter].lineNo = lineno;
    temparr[counter].clasPart = "$";
    temparr[counter].valuePart = "$";

    counter++;

    writeInFile(tokenFile);
   /* for(int u=0;u<counter;u++)
    {
        cout<< temparr[counter].valuePart<<endl;
        cout<< temparr[counter].clasPart<<endl;
        cout<<temparr[counter].lineNo<<endl;

    }*/
    syntaxAnalyzer(sizee);
    semanticAnalyzer();

}
