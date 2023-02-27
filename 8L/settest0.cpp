#include <cassert>
#include "set.h"
using namespace std;

int main(){
   Set t;
   
   // test find and insert
   assert(t.find("hello")==false);
   assert(t.insert("hello")==true);
   assert(t.find("hello")==true);
   assert(t.size()==1);
   
   assert(t.insert("hello")==false);
   assert(t.find("hello")==true);
   assert(t.size()==1);
   
   // test erase
   assert(t.erase("hello")==true);
   assert(t.find("hello")==false);
   assert(t.size()==0);
   
   assert(t.erase("hell")==false);
   assert(t.find("hell")==false);
   assert(t.size()==0);

}