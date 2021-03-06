#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
using namespace std;

bool
myStr2Int(const string& str, int& num)
{
   num = 0;
   size_t i = 0;
   int sign = 1;
   if (str[0] == '-') { sign = -1; i = 1; }
   bool valid = false;
   for (; i < str.size(); ++i) {
      if (isdigit(str[i])) {
         num *= 10;
         num += int(str[i] - '0');
         valid = true;
      }
      else return false;
   }
   num *= sign;
   return valid;
}


class All_via
{
public:
  All_via(){};
  virtual ~All_via(){};
  virtual string getTypeStr() const = 0;
  virtual int get_x()const = 0;
  virtual int get_y()const = 0;
  virtual int get_type()const = 0;
  virtual All_via* get_parent()const = 0;
//protected:

  vector<All_via*>possible_rvia;
  vector<int>rvia_type;
};

class rvia : public All_via
{
public:
  rvia(int x  , int y ,int type , All_via* parent):x_pos(x) , y_pos(y) , type(type) , parent(parent) {};
  ~rvia(){};
  string getTypeStr()const{return "rvia";}
  int get_x()const{return x_pos;}
  int get_y()const{return y_pos;}
  int get_type()const{return type;}
  All_via* get_parent()const{return parent;}
  int x_pos;
  int y_pos;
  int type;
  All_via* parent;
  
};

class via : public All_via
{
public:
  via(int x  , int y ):x_pos(x) , y_pos(y) {};
  ~via(){};
  string getTypeStr()const{return "via";}
  int get_x()const{return x_pos;}
  int get_y()const{return y_pos;}
  int get_type()const{return 0;}
  All_via* get_parent()const{return 0;}
  int x_pos;
  int y_pos;

  
};

int
Find_total(vector<vector< vector<All_via*> > >& board , int x_pos , int y_pos)
{
  int idx = 0;
  int x = 0;
  int y = 0;
  while(board[x_pos][y_pos][idx]!=0)
  {
    //cout<<board[x_pos][y_pos][idx]->get_x()<<","<<board[x_pos][y_pos]][idx]->get_y()<<endl;
    x = board[x_pos][y_pos][idx]->get_x();
    y = board[x_pos][y_pos][idx]->get_y();
    //cout<<x<<","<<y<<endl;
    ++idx;
  }
  return idx;
}



int main(int argc , char*argv[])
{
  /*if(argc!=3)
  {
    cerr<<"Missing document"<<endl;
  }*/

  string input_path = argv[1];
  ifstream ifs;
  ofstream ofs(argv[2],ios::out);
    string temp;
    int total_via = 0;
    //int col_num = 1000;
    //int row_num = 1000;
    //int overlap_num = 1000;

    //vector <vector<vector <All_via*> > > board(overlap_num,vector<vector <All_via*> >(row_num,vector<All_via*>(col_num,0)));
    //vector<All_via*>original_vias;
    vector<int>All_oriX;
    vector<int>All_oriY;

    ifs.open(input_path);
    while(getline(ifs,temp))
    {
    int x_pos = 0,y_pos = 0;
    int space = temp.find_first_of(' ');
    //cout<<"space: "<<space<<endl;
    if(space!=-1)
    {
     myStr2Int(temp.substr(0,space),x_pos);
     myStr2Int(temp.substr(space+1,string::npos),y_pos);
     //cout<<"x_pos: "<<x_pos<<endl;
     //cout<<"y_pos: "<<y_pos<<endl;

     All_oriX.push_back(x_pos);
     All_oriY.push_back(y_pos);

    }
    else 
    {
     myStr2Int(temp,total_via);
     //cout<<"total_via: "<<total_via<<endl;
    }   
    }
    cout<<"total_via: "<<total_via<<endl;
    ifs.close();

    int col_temp,row_temp;

    if(total_via>=10000)
    {
      col_temp = 5000;
      row_temp = 5000;
      //overlap_temp = 1000;
    }
    else if(total_via<10000)
    {
      col_temp = 1000;
      row_temp = 1000;
      //overlap_temp = 1000;
    }

    int col_num = col_temp;
    int row_num = row_temp;
    int overlap_num = 50;

    vector <vector<vector <All_via*> > > board(row_num,vector<vector <All_via*> >(col_num,vector<All_via*>(overlap_num,0)));
    vector<All_via*>original_vias;

    for(int k = 0 ; k<All_oriX.size() ; ++k)
    {
      int x_pos = All_oriX[k];
      int y_pos = All_oriY[k];

      board[x_pos][y_pos][0] = new via(x_pos,y_pos);
      original_vias.push_back(board[x_pos][y_pos][0]);  
    }

    set< pair<int,int> > overlap_pos;
    vector <vector<int> > overlap_pos_index(row_num,vector<int>(col_num,1));

    for(int m = 0 ; m<All_oriX.size() ; ++m)
    {
      int x_pos = All_oriX[m];
      int y_pos = All_oriY[m];
      All_via* temp = (board[x_pos][y_pos][0]);
      int pos1_x = x_pos;
      int pos1_y = y_pos+1;
      int pos2_x = x_pos+1;
      int pos2_y = y_pos;
      int pos3_x = x_pos;
      int pos3_y = y_pos-1;
      int pos4_x = x_pos-1;
      int pos4_y = y_pos;

      //temp : temp via

     //type one
     if(pos1_x>=0 && pos1_y>=0)
     {
      //int overlap_count = 0;
      if(board[pos1_x][pos1_y][0]==0) // empty now
      {
        board[pos1_x][pos1_y][0] = new rvia(pos1_x,pos1_y,1,board[x_pos][y_pos][0]);
        All_via* type_one = board[pos1_x][pos1_y][0];
        temp->possible_rvia.push_back(type_one);
        temp->rvia_type.push_back(1);

      }
      else if(board[pos1_x][pos1_y][0]->getTypeStr() == "rvia") // for constraint
      {
        //++overlap_count;
        int temp_idx = overlap_pos_index[pos1_x][pos1_y];
        board[pos1_x][pos1_y][temp_idx] = new rvia(pos1_x,pos1_y,1,board[x_pos][y_pos][0]);
        ++overlap_pos_index[pos1_x][pos1_y];
        //cout<<"push_back overlap"<<endl;
        //cout<<"overlap_pos_index[pos1_x][pos1_y]: "<<overlap_pos_index[pos1_x][pos1_y]<<endl;
        pair<int,int> p1 ;
        p1.first = pos1_x;
        p1.second = pos1_y;
        overlap_pos.insert(p1);
        All_via* type_one = board[pos1_x][pos1_y][0]; 
        temp->possible_rvia.push_back(type_one);
        temp->rvia_type.push_back(1);
      }
     }

     //type two
     if(pos2_x>=0 && pos2_y>=0)
     {
      //int overlap_count = 0;
      if(board[pos2_x][pos2_y][0]==0) // empty now
      {
        board[pos2_x][pos2_y][0] = new rvia(pos2_x,pos2_y,2,board[x_pos][y_pos][0]);
        All_via* type_two = board[pos2_x][pos2_y][0];
        temp->possible_rvia.push_back(type_two);
        temp->rvia_type.push_back(2);

      }
      else if(board[pos2_x][pos2_y][0]->getTypeStr() == "rvia") // for constraint
      {
        //++overlap_count;
        int temp_idx = overlap_pos_index[pos2_x][pos2_y];
        board[pos2_x][pos2_y][temp_idx] = new rvia(pos2_x,pos2_y,2,board[x_pos][y_pos][0]);
        ++overlap_pos_index[pos2_x][pos2_y];
        //cout<<"push_back overlap"<<endl;
        //cout<<"overlap_pos_index[pos2_x][pos2_y]: "<<overlap_pos_index[pos2_x][pos2_y]<<endl;
        pair<int,int> p2 ;
        p2.first = pos2_x;
        p2.second = pos2_y;
        overlap_pos.insert(p2);
        All_via* type_two = board[pos2_x][pos2_y][0];
        temp->possible_rvia.push_back(type_two);
        temp->rvia_type.push_back(2);
      }
     }

     //type three
     if(pos3_x>=0 && pos3_y>=0)
     {
      //int overlap_count = 0;
      if(board[pos3_x][pos3_y][0]==0) // empty now
      {
        board[pos3_x][pos3_y][0] = new rvia(pos3_x,pos3_y,3,board[x_pos][y_pos][0]);
        All_via* type_three = board[pos3_x][pos3_y][0];
        temp->possible_rvia.push_back(type_three);
        temp->rvia_type.push_back(3);

      }
      else if(board[pos3_x][pos3_y][0]->getTypeStr() == "rvia") // for constraint
      {
        //++overlap_count;
        int temp_idx = overlap_pos_index[pos3_x][pos3_y];
        board[pos3_x][pos3_y][temp_idx] = new rvia(pos3_x,pos3_y,3,board[x_pos][y_pos][0]);
        ++overlap_pos_index[pos3_x][pos3_y];
        //cout<<"push_back overlap"<<endl;
        //cout<<"overlap_pos_index[pos3_x][pos3_y]: "<<overlap_pos_index[pos3_x][pos3_y]<<endl;
        pair<int,int> p3 ;
        p3.first = pos3_x;
        p3.second = pos3_y;
        overlap_pos.insert(p3);
        All_via* type_three = board[pos3_x][pos3_y][0];
        temp->possible_rvia.push_back(type_three);
        temp->rvia_type.push_back(3);
      }
     }

     //type four
     if(pos4_x>=0 && pos4_y>=0)
     {
      //int overlap_count = 0;
      if(board[pos4_x][pos4_y][0]==0) // empty now
      {
        board[pos4_x][pos4_y][0] = new rvia(pos4_x,pos4_y,4,board[x_pos][y_pos][0]);
        All_via* type_four = board[pos4_x][pos4_y][0];
        temp->possible_rvia.push_back(type_four);
        temp->rvia_type.push_back(4);

      }
      else if(board[pos4_x][pos4_y][0]->getTypeStr() == "rvia") // for constraint
      {
        //++overlap_count;
        int temp_idx = overlap_pos_index[pos4_x][pos4_y];
        board[pos4_x][pos4_y][temp_idx] = new rvia(pos4_x,pos4_y,4,board[x_pos][y_pos][0]);
        ++overlap_pos_index[pos4_x][pos4_y];
        //cout<<"push_back overlap"<<endl;
        //cout<<"overlap_pos_index[pos4_x][pos4_y]: "<<overlap_pos_index[pos1_x][pos1_y]<<endl;
        pair<int,int> p4 ;
        p4.first = pos4_x;
        p4.second = pos4_y;
        overlap_pos.insert(p4);
        All_via* type_four = board[pos4_x][pos4_y][0];
        temp->possible_rvia.push_back(type_four);
        temp->rvia_type.push_back(4);
      }
     }

    }

    ///
    ofs<<"Maximize"<<endl;
    for(int i = 0 ; i<original_vias.size() ; ++i)
    {
      if(original_vias[i]->rvia_type.size()!=0)
      {
      ofs<<"    ";
      for(int j = 0; j<original_vias[i]->rvia_type.size(); ++j)
      {
        ofs<<"R_"<<original_vias[i]->get_x()<<"_"<<original_vias[i]->get_y()<<"_"<<original_vias[i]->rvia_type[j];
        if(i!=original_vias.size()-1 || j!=original_vias[i]->rvia_type.size()-1)
        {
          ofs<<" + ";
        }
      }
      }
      else
      {
        continue;
      }
      ofs<<endl;
    }
    ofs<<"Subject To"<<endl;
    for(int i = 0 ; i<original_vias.size() ; ++i)
    {
      if(original_vias[i]->rvia_type.size()!=0)
      {
      ofs<<"    ";
      //ofs<<"R_"<<original_vias[i]->get_x()<<"_"<<original_vias[i]->get_y()<<":";
      for(int j = 0; j<original_vias[i]->rvia_type.size(); ++j)
      {
        ofs<<"R_"<<original_vias[i]->get_x()<<"_"<<original_vias[i]->get_y()<<"_"<<original_vias[i]->rvia_type[j];
        if(j!=original_vias[i]->rvia_type.size()-1)
        {
          ofs<<" + ";
        }
      }
      }
      else
      {
        continue;
      }
      ofs<<" <= 1 ";
      ofs<<endl;
    }

    //cout<<"size: "<<overlap_pos.size()<<endl;

    set< pair<int,int> >::iterator it;
    int i = 1;
    for(it=overlap_pos.begin();it!=overlap_pos.end();++it)
    {
      int x_pos = it->first;
      int y_pos = it->second;
      //cout<<"x_pos: "<<x_pos<<endl;
      //cout<<"y_pos: "<<y_pos<<endl;
      ofs<<"    ";
      //ofs<<"C"<<i<<":";

      for(int j = 0 ; j<overlap_pos_index[x_pos][y_pos] ; ++j)
      {
        ofs<<"R_"<<board[x_pos][y_pos][j] -> get_parent() -> get_x()<<"_"<<board[x_pos][y_pos][j] -> get_parent() -> get_y()<<"_"<<board[x_pos][y_pos][j] -> get_type();
        if(j!=overlap_pos_index[x_pos][y_pos]-1)
        {
          ofs<<" + ";
        }
      }
      ofs<<" <= 1 ";
      ofs<<endl;
      ++i;
    }


    ofs<<"Bounds"<<endl;
    //ofs<<'\n';
    ofs<<"Binary"<<endl;
    for(int i = 0 ; i<original_vias.size() ; ++i)
    {
      if(original_vias[i]->rvia_type.size()!=0)
      {
      ofs<<"    ";
      for(int j = 0; j<original_vias[i]->rvia_type.size(); ++j)
      {
      ofs<<"R_"<<original_vias[i]->get_x()<<"_"<<original_vias[i]->get_y()<<"_"<<original_vias[i]->rvia_type[j];
      ofs<<" ";
      }
      }
      else
      {
        continue;
      }
      ofs<<endl;
    }
    ofs<<"End"<<endl;

}