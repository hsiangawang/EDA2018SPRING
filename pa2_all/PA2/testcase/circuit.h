#include <string>
#include <vector>
#include <iostream>

using namespace std;

class CirGate;

class CirGate
{
public:
   CirGate( vector<int> faninList, int fanout): faninList(faninList), fanout(fanout)  {}
   virtual ~CirGate() {}
   virtual  string getTypeCNF() const = 0;   

private:

protected:

  vector<int> faninList;
  int fanout;

};


class ANDgate: public CirGate
{
public:
  ANDgate(vector<int> faninList, int fanout)   
  :CirGate( vector<int> faninList , int fanout )  {}  ;
  ~ANDgate(){};

  string getTypeCNF()
  {

  }

};

class NANDgate: public CirGate
{
public:
  NANDgate(vector<int> faninList, int fanout)   
  :CirGate( vector<int> faninList , int fanout )  {}  ;
  ~NANDgate(){};

  string getTypeCNF()
  {

  }

};

class ORgate: public CirGate
{
public:
  ORgate(vector<int> faninList, int fanout)   
  :CirGate( vector<int> faninList , int fanout )  {}  ;
  ~ORgate(){};

  string getTypeCNF()
  {

  }

};

class NORgate: public CirGate
{
public:
  NORgate(vector<int> faninList, int fanout)   
  :CirGate( vector<int> faninList , int fanout )  {}  ;
  ~NORgate(){};

  string getTypeCNF()
  {

  }

};

class NOTgate: public CirGate
{
public:
  NOTgate(vector<int> faninList, int fanout)   
  :CirGate( vector<int> faninList , int fanout )  {}  ;
  ~NOTgate(){};

  string getTypeCNF()
  {

  }

};

class XORgate: public CirGate
{
public:
  XORgate(vector<int> faninList, int fanout)   
  :CirGate( vector<int> faninList , int fanout )  {}  ;
  ~XORgate(){};

  string getTypeCNF()
  {

  }

};

class EQVgate: public CirGate
{
public:
  EQVgate(vector<int> faninList, int fanout)   
  :CirGate( vector<int> faninList , int fanout )  {}  ;
  ~EQVgate(){};

  string getTypeCNF()
  {

  }

};

class BUFgate: public CirGate
{
public:
  BUFgate(vector<int> faninList, int fanout)   
  :CirGate( vector<int> faninList , int fanout )  {}  ;
  ~BUFgate(){};

  string getTypeCNF()
  {

  }

};
 