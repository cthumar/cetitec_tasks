#include "console_spreadsheet.h"

Cells::Cells(size_t rowSize,size_t colSize) {
    this->table.resize(rowSize+1);
    for(int i=0; i < this->table.size() ;i++) this->table[i].resize(colSize+1);
    this->row_size=rowSize;
    this->col_size=colSize;
}

std::string Cells::operator()(char col, int row){
    int c= (int)col -'A';
    std::string result = "NAN";
    if((c >= 0) && (row>0))
    {
        result=this->table[row-1][c];
    }
    return result;
}

std::string& Cells::operator()(int row, int col){
    if(row >= this->row_size) {
        this->table.resize(row+1);
        this->row_size++;
        this->table[row].resize(this->col_size);
    }
    if(col >= this->col_size) {
        for(int i=0; i < this->table.size() ;i++) 
        this->table[i].resize(col+1);this->col_size;
        this->col_size++;
    }
    return this->table[row][col];
}

//Spreadsheet class***************************************************************/

Spreadsheet::Spreadsheet(std::string filename) : cell_table(1,1)
{
    this->inStream.open(filename,std::ios::binary);
}

Spreadsheet::~Spreadsheet()
{
    if(this->inStream.is_open())this->inStream.close();
}

void Spreadsheet::parseTextFile()
{
    string  line;
    string  cellValue;
    int i=0,j=0;

    while(getline(this->inStream,line))
    {   j=0;
        stringstream          lineStream(line);
        while(getline(lineStream,cellValue, '\t'))
        {
            //remove return or endline character
            if(!cellValue.empty()  && cellValue[cellValue.length()-1] == '\r')
            {
                cellValue.erase(cellValue.length()-1);
            }
            this->cell_table(i,j)=cellValue;
            j++;
        }
        i++;
    }

    //cout<<"Nr of rows: "<<this->cell_table.row_size<<endl;
    //cout<<"Nr of columns: "<<this->cell_table.col_size <<endl;
}

void Spreadsheet::evaluate()
{
    for(int r=0; r<this->cell_table.row_size; r++)
    {
        for(int c=0; c < this->cell_table.col_size; c++)
        {
            if(this->cell_table(r,c).find('=') != std::string::npos)
            { 
                char colname=(char)('A'+ c);
                string cellName{colname};
                cellName.append(to_string(r+1));
                this->string_calculator(c,r,this->cell_table(r,c),cellName);
            }
        }
    }
}

void Spreadsheet::string_calculator(int col, int row, string str, string currentCellName)
{
    vector<string> cellAdresses;
    vector<string> v_operators;
    int res=0;
    str.erase(0,1);
    
    std::regex isValidOpertion(R"(^([A-Z]\d+[\+-\/\*])+([A-Z]\d+)$)");
    auto matches=std::smatch{};
    if(!regex_search(str,matches,isValidOpertion))
    {
        this->cell_table(col,row)="#ERROR";
        return;
    }
    
    //create a vector list of all cell names
    string::const_iterator searchStart( str.cbegin() );
    string result="#ERROR";
    std::regex regex_cellnames(R"([A-Z]\d+)");
    auto mtchs=std::smatch{};
    while ( regex_search( searchStart, str.cend(), matches, regex_cellnames ) )
    {
        auto addr_str=matches[0].str();
        int r = getRowValue(addr_str);
        int colum = getColValue(addr_str);
        if(this->cell_table(addr_str[0],r+1).find('=') != std::string::npos)
        {
            if(this->cell_table(addr_str[0],r+1).find(currentCellName) != std::string::npos)
            {   //circular dependancy found!
                this->cell_table(row,col)="#ERROR";
                this->cell_table(r,colum)="#ERROR";
                return;
            }
            char colname=(char)('A'+ colum);
            string cellName{colname};
            cellName.append(to_string(r+1));
            this->string_calculator(colum,r,this->cell_table(r,colum),cellName);
        }
        
        cellAdresses.push_back(matches[0].str()); 
        searchStart = matches.suffix().first;
    }

    //create a vector list of all operators
    searchStart=str.cbegin();
    std::regex regex_operator(R"([\+-\/\*])");
    while ( regex_search( searchStart, str.cend(), matches, regex_operator ) )
    {
        v_operators.push_back(matches[0].str()); 
        searchStart = matches.suffix().first;
    }
    
    int a,b;
    result="OK";
    //perform the arithmetic calculation here
    for(int i=0; i < v_operators.size(); i++)
    {
        
        if(v_operators[i] == "+")
        {
            if(i==0)
            {
                a=getCellValue(cellAdresses[i],result);
                if(result != "#NAN") res+=a;
            }
            if(result != "#NAN") b=getCellValue(cellAdresses[i+1],result);
            if(result != "#NAN") res+=b;         
        }
        else if(v_operators[i] == "-")
        {
            if(i==0)
            {
                a=getCellValue(cellAdresses[i],result);
                if(result != "#NAN") res-=a;
            }
            if(result != "#NAN") b=getCellValue(cellAdresses[i+1],result);
            if(result != "#NAN") res-=b;    
        }
        else if(v_operators[i] == "*")
        {
            if(i==0)
            {
                a=getCellValue(cellAdresses[i],result);
                if(result != "#NAN") res=a*1;
            }
            if(result != "#NAN") b=getCellValue(cellAdresses[i+1],result);
            if(result != "#NAN") res*=b;    
        }
        else if(v_operators[i] == "/")
        {
            if(i==0)
            {
                a=getCellValue(cellAdresses[i],result);
                if(result != "#NAN") res=a*1;
            }
            if(result != "#NAN") b=getCellValue(cellAdresses[i+1],result);
            if(result != "#NAN")
            {
                if(b != 0)res/=b; 
                else result="#ERROR";
            }   
        }
        
    }
    if((result != "#NAN") && (result != "#ERROR"))result=to_string(res);
    this->cell_table(row,col)=result;
}


void Spreadsheet::streamOutput(ostream& cout)
{
    for(int i=0; i < this->cell_table.row_size;i++)
    {
        for(int j=0; j < this->cell_table.col_size;j++)
        {
            cout<<this->cell_table(i,j)<<"\t"; 
        }
        cout<<endl;
    }
}

int Spreadsheet::getCellValue(string str, string& rslt)
{
    int value=0;
    int r = stoi(str.substr(1,str.length()-1))-1;
    int c = str[0]-'A';
    string s_str=this->cell_table(r,c);
    if(s_str != "") {value=stoi(s_str);rslt="OK";}
    else rslt = "#NAN";
    return value;
}

int Spreadsheet::getRowValue(string str)
{
    int r = stoi(str.substr(1,str.length()-1))-1;
    return r;
}
int Spreadsheet::getColValue(string str)
{
    int c = str[0]-'A';
    return c;
}

