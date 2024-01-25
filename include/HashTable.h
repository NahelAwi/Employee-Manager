#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include "UnionFindNode.h"


#define TABLESIZE 1000


enum EntryType {Taken, Empty, Dead};

class HashTableEntry{
    public:
        int EmployeeID;
        int salary;
        int grade;
        UnionFindNode* Company;
        HashTableEntry* Next;
};




class HashTable {
   public:
      int size;
      int NumOfEmployees;
      HashTableEntry *table;
   
   HashTable(){
      size = TABLESIZE;
      NumOfEmployees = 0;
      table = initiateTable(TABLESIZE);
   }
	~HashTable(){
		HashTableEntry *ptr;
		for(int i=0 ; i<size ; i++){
			while(table[i].Next != nullptr ){
				ptr=table[i].Next;
				table[i].Next = ptr->Next;
				delete ptr;
			}
		}
		delete[] table;
	}

   int HashFunc1(int k, int s) {
      return k % s;
   }

   HashTableEntry* SearchEmployeeID(int id) {
      int hashVal= HashFunc1(id, size);
      HashTableEntry* ptr = table[hashVal].Next;
      while(ptr != nullptr){
          if(ptr->EmployeeID == id) return ptr;
          ptr = ptr->Next;
      }
      return nullptr;
   }

   UnionFindNode* find(int EmployeeId){
      HashTableEntry* ptr = SearchEmployeeID(EmployeeId);
      //std::cout << "     " << pos << "    " << table[pos].EmployeeID << "    " <<table[pos].info  ;
        if(ptr == nullptr) return nullptr;
        return ptr->Company;
   }

   bool find2(int EmployeeId){
      HashTableEntry* ptr = SearchEmployeeID(EmployeeId);
      //std::cout << "     " << pos << "    " << table[pos].EmployeeID << "    " <<table[pos].info  ;
        if(ptr == nullptr) return false;
        return true;
   }

   

   bool add(int EmployeeID, int salary, int grade, UnionFindNode* Company){
      //if(NumOfEmployees >= size/2) MethodReHash();
      if(find2(EmployeeID) == true) return false;
      HashTableEntry* ptr = table[HashFunc1(EmployeeID,size)].Next;
      if(ptr == nullptr){
          ptr = new HashTableEntry();
          table[HashFunc1(EmployeeID,size)].Next = ptr;
          ptr->EmployeeID = EmployeeID;
          ptr->salary = salary;
          ptr->grade = grade;
          ptr->Company = Company;
          NumOfEmployees++;
      }else{
          //while(ptr->Next != nullptr) {
          //  ptr = ptr->Next;
          //}
          //ptr->Next = new HashTableEntry();
          //ptr = ptr->Next; 
          table[HashFunc1(EmployeeID,size)].Next = new HashTableEntry();
          table[HashFunc1(EmployeeID,size)].Next->Next = ptr;
          table[HashFunc1(EmployeeID,size)].Next->EmployeeID = EmployeeID;
          table[HashFunc1(EmployeeID,size)].Next->salary = salary;
          table[HashFunc1(EmployeeID,size)].Next->grade = grade;
          table[HashFunc1(EmployeeID,size)].Next->Company = Company;
          NumOfEmployees++;
      }
      
         return true;
   }

   bool remove(int EmployeeID){
      if(find2(EmployeeID) == false) return false;
      //std::cout << " removing ";
      HashTableEntry* Employee;
      HashTableEntry* ptr = &table[HashFunc1(EmployeeID,size)];
     
        while(ptr->Next != nullptr && ptr->Next->EmployeeID != EmployeeID){
            ptr = ptr->Next;
        }
      if(ptr->Next != nullptr) {
         Employee = ptr->Next;
         ptr->Next = ptr->Next->Next;
      }
      delete Employee;
      NumOfEmployees--;

      return true;
   }

   HashTableEntry* initiateTable(int size) {
        HashTableEntry *table = new HashTableEntry[size];
        if(table == nullptr) throw std::bad_alloc();
        for (int i = 0; i < size; i++) {
            table[i].EmployeeID = 0;
            table[i].salary = 0;
            table[i].grade = 0;
            table[i].Next = nullptr;
            table[i].Company = nullptr;
        }
        return table;
    }

};

/*
void display(HashTable *ht) {
   for (int i = 0; i < ht->size; i++) {
      HashTableEntry* v = ht->table[i].Next;
      while(v != nullptr){
      if (!v)
         std::cout<<"Position: "<<i<<" ID: Null  "<< "salary: "<< ht->table[i].salary << "grade: "<< ht->table[i].grade <<std::endl;
      else
         std::cout<<"Position: "<<i<<" ID: "<<v->EmployeeID <<"    " << "salary: "<< ht->table[i].salary << "grade: "<< ht->table[i].grade <<std::endl;
      v = v->Next;
   }
   }
}


int main() {
   int v, s, pos, i = 1;
   int c;
   HashTable *ht;
      std::cout<<"1.Initialize size of the table"<<std::endl;
      std::cout<<"2.Insert element into the table"<<std::endl;
      std::cout<<"3.Display Hash Table"<<std::endl;
      std::cout<<"4.Rehash Hash Table"<<std::endl;
      std::cout<<"5.Exit"<<std::endl;
      std::cout<<"6.delete"<<std::endl;
      std::cout<<"Enter your choice: ";
   while(1) {
      std::cin>>c;
      switch(c) {
         case 1:
            std::cout<<"Enter size of the Hash Table: ";
            std::cin>>s;
            ht->table = ht->initiateTable(2*s);
            ht->size = 2*s;
         break;
         case 2:
            if (i > ht->size) {
               std::cout<<"Table is Full, Rehash the table"<<std::endl;
               continue;
            }
            std::cout<<"Enter element to be inserted: ";
            std::cin>>v;
            ht->add(v,0,0,nullptr );
            i++;
         break;
         case 3:
            display(ht);
         break;
         case 4:
            //ht= Rehash(ht);
         break;
         case 5:
            exit(1);
         case 6:
            std::cout<<"Enter element to be deleted: ";
            std::cin>>v;
            ht->remove(v);
            i--;
         break;
            
         default:
         std::cout<<"\nEnter correct option\n";
      }
   }
   return 0;
}

*/


#endif // HASH_TABLE_H