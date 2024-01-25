

#ifndef EMPLOYEERANKTREE_H
#define EMPLOYEERANKTREE_H

#include <iostream>
#include "EmployeeRankNode.h"

class EmployeeRankTree {
public:
    EmployeeRankNode* Root;


    EmployeeRankTree(){
        Root = nullptr;
    }

    ~EmployeeRankTree() {
        DestroyTree(this->Root);
    }



    /// function that destroy the tree in recursive way
    void DestroyTree(EmployeeRankNode* root) {
        if (root == nullptr)
            return;
        DestroyTree(root->LeftSon);
        DestroyTree(root->RightSon);
        delete root;
    }

    
    EmployeeRankNode *Search(int employeeId){
        if (this->Root == nullptr) {
            return nullptr;
        }
        EmployeeRankNode *ptr = this->Root;
        while (ptr != nullptr) {
            if (ptr->employee.employeeId == employeeId) {
                return ptr;
            }
            else if (ptr->employee.employeeId < employeeId){
                ptr = ptr->RightSon;
            }
            else{
                ptr = ptr->LeftSon;
            }
        }
        return nullptr;
    }

    void SearchAndDelete(int employeeId, int grade){
        if(this->Root == nullptr) {
            return;
        }
        EmployeeRankNode *ptr = this->Root;
        while (ptr != nullptr) {
            if (ptr->employee.employeeId == employeeId) {
                ptr->employee.Grade -= grade;
                ptr->employee.CoTreeGrade -= grade;
                return;
            }
            else if (ptr->employee.employeeId < employeeId){
                ptr->employee.CoTreeGrade -= grade;
                ptr = ptr->RightSon;
            }
            else{
                ptr->employee.CoTreeGrade -= grade;
                ptr = ptr->LeftSon;
            }
        }
        return;
    }

    void SearchAndAdd(int employeeId, int grade){
        if (this->Root == nullptr) {
            return;
        }
        EmployeeRankNode *ptr = this->Root;
        while (ptr != nullptr) {
            if (ptr->employee.employeeId == employeeId) {
                ptr->employee.CoTreeGrade += grade;
                ptr->employee.Grade += grade;
                return;
            }
            else if (ptr->employee.employeeId < employeeId){
                ptr->employee.CoTreeGrade += grade;
                ptr = ptr->RightSon;
            }
            else{
                ptr->employee.CoTreeGrade += grade;
                ptr = ptr->LeftSon;
            }
        }
        return;
    }

    void SearchAndNum(int employeeId , int &grades,int &num,int &numInsalary,int &GradesInsalary){
        if (this->Root == nullptr) {
            return;
        }
        EmployeeRankNode *ptr = this->Root;
        while (ptr != nullptr) {
            if(ptr->employee.employeeId == employeeId && ptr->LeftSon == nullptr){
                    GradesInsalary = ptr->employee.Grade;
                    grades += ptr->employee.Grade;
                    return;
            }
            else if(ptr->employee.employeeId == employeeId){
                    GradesInsalary = ptr->employee.Grade;
                    grades += (ptr->employee.Grade += ptr->LeftSon->employee.CoTreeGrade);
                    return;
            }
            else if (ptr->employee.employeeId < employeeId && ptr->LeftSon == nullptr ){
                    grades += ptr->employee.Grade;
                    ptr = ptr->RightSon;
            }
            else if(ptr->employee.employeeId < employeeId){
                    grades += (ptr->employee.Grade += ptr->LeftSon->employee.CoTreeGrade);
                    ptr = ptr->RightSon;
            }
            else if(ptr->employee.employeeId > employeeId){
                ptr = ptr->LeftSon;
            }
        }
    }

    void SearchAndSum(int employeeId ,int &sum){
        if (this->Root == nullptr) {
            return;
        }
        EmployeeRankNode *ptr = this->Root;
        while (ptr != nullptr) {
            if (ptr->employee.employeeId == employeeId){
                if(ptr->LeftSon == nullptr) sum += ptr->employee.Grade;
                else sum += (ptr->employee.employeeId + ptr->LeftSon->employee.CoTreeGrade);
                return;
            }
           else if (ptr->employee.employeeId < employeeId){
                if(ptr->LeftSon == nullptr) sum += ptr->employee.Grade;
                else sum += (ptr->employee.Grade + ptr->LeftSon->employee.CoTreeGrade);
                ptr = ptr->RightSon;
            }
            else{
                ptr = ptr->LeftSon;
            }
        }
    }

    void SearchAndBumpGrade(int employeeId, int BumpGrade){
        if (this->Root == nullptr) {
            return;
        }
        EmployeeRankNode *ptr = this->Root;
        while (ptr != nullptr) {
            if (ptr->employee.employeeId == employeeId) {
                ptr->employee.Grade += BumpGrade;
                ptr->employee.CoTreeGrade += BumpGrade;
                return;
            }
            else if (ptr->employee.employeeId < employeeId){
                ptr->employee.CoTreeGrade += BumpGrade;
                ptr = ptr->RightSon;
            }
            else{
                ptr->employee.CoTreeGrade += BumpGrade;
                ptr = ptr->LeftSon;
            }
        }
        return;
    }

    
    bool Insert(const Employee& employee){
        if (this->Root == nullptr) {

            this->Root = new EmployeeRankNode(employee);

            if(this->Root == nullptr) throw std::bad_alloc();
            this->Root->w = 1;
        } else {

            EmployeeRankNode *p, *son = Root;
            while (true) {
                p = son; /// hold the father in P

                if(son->employee.employeeId == employee.employeeId){
                    return false;  
                }else{ 
                    if(son->employee.employeeId > employee.employeeId){
                    son->w += 1;
                    son->employee.CoTreeGrade += employee.Grade;
                    son = son->LeftSon;   
                }else{
                    son->w += 1;
                    son->employee.CoTreeGrade += employee.Grade;;
                    son = son->RightSon;
                    }
                }
                    
                if (son == nullptr) {
                    if(p->employee.employeeId > employee.employeeId){
                        EmployeeRankNode* tmp = new EmployeeRankNode(employee);
                        if(tmp == nullptr) throw std::bad_alloc();
                        p->LeftSon = tmp;
                        p->LeftSon->Parent = p;
                        p->LeftSon->w = 1;
                    }else{
                        EmployeeRankNode* tmp = new EmployeeRankNode(employee);
                        if(tmp == nullptr) throw std::bad_alloc();
                        p->RightSon = tmp;
                        p->RightSon->Parent = p;
                        p->RightSon->w = 1;
                    }
                    break;
                }
            }
        }
        return true;
    }



    void GetRightestSum(int &sum){
        if(this->Root == nullptr)
            return;
        EmployeeRankNode *ptr1 = this->Root;

        while(ptr1 != nullptr){
            if(ptr1->LeftSon == nullptr) sum += ptr1->employee.Grade;
            else sum += (ptr1->employee.Grade + ptr1->LeftSon->employee.CoTreeGrade);
            ptr1 = ptr1->RightSon;
        }
        return;

    }




    void removeByCase(EmployeeRankNode* root){
        if ((!root->LeftSon) && (!root->RightSon)){//No Sons
            if (root == Root){
                Root = NULL;
                delete root;
                return;
            }
            
            if ((root->Parent)->RightSon == root){
                root->Parent->RightSon = nullptr;
            } else {
                root->Parent->LeftSon = nullptr;
            }
            delete root;
            return;
        }//
        
        if ((!root->LeftSon) && (root->RightSon)){//One Right Son
            if (root == Root){
                root->RightSon->Parent = nullptr;
                Root=root->RightSon;
                delete root;
                return;
            }
            
            if ((root->Parent)->RightSon == root){
                root->Parent->RightSon = root->RightSon;
            } else {
                root->Parent->LeftSon = root->RightSon;
            }
            root->RightSon->Parent = root->Parent;
            delete root;
            return;
        }//
        
        if ((root->LeftSon) && (!root->RightSon)){//One Left Son
            if (root == Root){
                root->LeftSon->Parent = nullptr;
                Root=root->LeftSon;
                delete root;
                return;
            }
            
            if ((root->Parent)->RightSon == root){
                root->Parent->RightSon = root->LeftSon;
            } else {
                root->Parent->LeftSon = root->LeftSon;
            }
            root->LeftSon->Parent = root->Parent;
            delete root;
            return;
        }//
    }
    
    void removeNode(EmployeeRankNode* root, const Employee& employee){
        if (root->employee.employeeId == employee.employeeId){
			
            if ((root->RightSon) && (root->LeftSon)){//Two Sons
                EmployeeRankNode* followingNode = root->RightSon;
                while (followingNode->LeftSon){
                    followingNode = followingNode->LeftSon;
                }

                Employee temp = followingNode->employee ;
                removeNode(root, followingNode->employee);

                root->employee.employeeId = temp.employeeId;

                root->employee.CoTreeGrade = root->employee.CoTreeGrade - root->employee.Grade + temp.Grade;
                
                root->employee.Grade = temp.Grade;

                return;
            }//
            
            removeByCase(root);
            return;
            
        }
        
        if (root->employee.employeeId > employee.employeeId){
			root->w -= 1;
            root->employee.CoTreeGrade -= employee.Grade;
            removeNode(root->LeftSon,employee);
        } else {
			root->w -= 1;
            root->employee.CoTreeGrade -= employee.Grade;
            removeNode(root->RightSon,employee);
        }
    }


    void DeleteFromTree(int employeeID){
        EmployeeRankNode* Node = Search(employeeID);
        if(Node != nullptr){
            EmployeeRankNode* tmp = Root;
            while (tmp != Node)
            {
                if (tmp->employee.employeeId > employeeID){
			        tmp->w -= 1;
                    tmp->employee.CoTreeGrade -= Node->employee.Grade;
                    tmp = tmp->LeftSon;
                } else {
			        tmp->w -= 1;
                    tmp->employee.CoTreeGrade -= Node->employee.Grade;
                    tmp = tmp->RightSon;
                }
            }
            removeNode(Node, Node->employee);
        }
            
    }


    EmployeeRankNode* maxNode(EmployeeRankNode* root){
        EmployeeRankNode* p = Root;
        while(p->RightSon != nullptr) p = p->RightSon;
        return p;
    }

    EmployeeRankNode* minNode(EmployeeRankNode* root ){
        EmployeeRankNode* p = Root;
        while(p->LeftSon != nullptr) p = p->LeftSon;
        return p;
    }
    
    
    
    EmployeeRankNode* Select_rank(EmployeeRankNode* ptr,int Rank) {
        if (ptr == nullptr)
            return nullptr;

        if (ptr->LeftSon == nullptr && (Rank == 1))
            return ptr;

        if (ptr->LeftSon != nullptr) {
            if (ptr->LeftSon->w == Rank - 1)
                return ptr;

            if (ptr->LeftSon->w > Rank - 1)
                return Select_rank(ptr->LeftSon, Rank);
        }
        if (ptr->RightSon != nullptr && ptr->LeftSon != nullptr){
            int new_Rank = (Rank - ptr->LeftSon->w - 1);
            return Select_rank(ptr->RightSon, new_Rank);
        }

        if (ptr->RightSon != nullptr){
            int new_Rank = (Rank - 1);
            return Select_rank(ptr->RightSon, new_Rank);
        }
        return nullptr;
    }




    void PostOrder(EmployeeRankNode *node){
        if(node == nullptr)
            return;

        PostOrder(node->LeftSon);
        PostOrder(node->RightSon);

        if(node->RightSon == nullptr && node->LeftSon == nullptr){
            node->w = 1;
            node->employee.CoTreeGrade = node->employee.Grade;
            
        }
        if(node->RightSon == nullptr && node->LeftSon != nullptr){
            node->w  = node->LeftSon->w + 1;
            node->employee.CoTreeGrade = (node->LeftSon->employee.CoTreeGrade + node->employee.Grade);
 
            
        }
        if(node->RightSon != nullptr && node->LeftSon == nullptr){
            node->w  = node->RightSon->w + 1;
            node->employee.CoTreeGrade = (node->RightSon->employee.CoTreeGrade + node->employee.Grade);

        }
        if(node->RightSon != nullptr && node->LeftSon != nullptr){
            node->w  = node->RightSon->w +  node->LeftSon->w + 1;
            node->employee.CoTreeGrade = (node->LeftSon->employee.CoTreeGrade + node->RightSon->employee.CoTreeGrade + node->employee.Grade);
        }
    }


    int MergeSortedArrays(EmployeeRankNode** array1,EmployeeRankNode** array2,EmployeeRankNode** array3,int n1,int n2){
        int i=0,j=0,k=0;
        while (i<n1 && j<n2){
            if(array1[i]->employee.employeeId < array2[j]->employee.employeeId)
                array3[k++] = array1[i++];
            else if(array1[i]->employee.employeeId > array2[j]->employee.employeeId)
                array3[k++] = array2[j++];
            else{
                array3[k++] = array1[i];
                i++;
                j++;
            }
        }
        
        while(i<n1)
            array3[k++]=array1[i++];
        while(j<n2)
            array3[k++]=array2[j++];
        
        return k;
    }

    EmployeeRankNode* FromArrayToTree(EmployeeRankNode** array,int start,int end){
        if(start>end)
            return nullptr;
        int mid= (start+end)/2;
        EmployeeRankNode* root = new EmployeeRankNode(array[mid]->employee);
        if(root == nullptr) throw std::bad_alloc();
        root->LeftSon =  FromArrayToTree(array,start,mid-1);
        root->RightSon = FromArrayToTree(array,mid+1,end);
        return root;
    }


    int FromTreeToArray(EmployeeRankNode** array,EmployeeRankNode* node,int index){
        if(!node)
            return index;
        if(node->LeftSon !=nullptr)
            index=FromTreeToArray(array,node->LeftSon,index);
        array[index]=node;
        index++;
        if(node->RightSon != nullptr)
            index=FromTreeToArray(array,node->RightSon,index);
        return index;
    }

    void FixParent(EmployeeRankNode* root) {
        if(!root)
            return;
        FixParent(root->LeftSon);
        if(root->RightSon)
            root->RightSon->Parent=root;
        if(root->LeftSon)
            root->LeftSon->Parent=root;
        FixParent(root->RightSon);
    }

    EmployeeRankNode* MergeRankTrees(EmployeeRankNode** tree1,EmployeeRankNode** tree2, int size1 , int size2){
        EmployeeRankNode** array_Of_tree1 = new EmployeeRankNode*[size1];
        EmployeeRankNode** array_Of_tree2 = new EmployeeRankNode*[size2];
        for(int i = 0; i < size1; i++){
            array_Of_tree1[i] = nullptr;
        }
        for(int j = 0; j < size2; j++){
            array_Of_tree2[j] = nullptr;
        }
        FromTreeToArray(array_Of_tree1,*tree1,0);
        FromTreeToArray(array_Of_tree2,*tree2,0);
        
        EmployeeRankNode** Merged_array = new EmployeeRankNode*[size1+size2];
        for(int i = 0; i < size1+size2; i++){
            Merged_array[i] = nullptr;
        }
        if(array_Of_tree1 == nullptr || array_Of_tree2 == nullptr || Merged_array == nullptr) throw std::bad_alloc();
        
    
        int k = MergeSortedArrays(array_Of_tree1,array_Of_tree2,Merged_array,size1,size2);

        EmployeeRankNode* root=FromArrayToTree(Merged_array,0, k - 1);
        FixParent(root);
        PostOrder(root);
        //DestroyTree(*tree1);
        //DestroyTree(*tree2);
        
        delete [] array_Of_tree1;
        delete [] array_Of_tree2;
        delete [] Merged_array;
        
        return root;
    }
};


#endif //EMPLOYEERANKTREE_H
