

#ifndef RANKTREE_H
#define RANKTREE_H

#include <iostream>
#include "RankTreeNode.h"

class RankTree {
public:
    RankTreeNode* Root;


    RankTree(){
        Root = nullptr;
    }

    ~RankTree() {
        DestroyTree(this->Root);
    }



    /// function that destroy the tree in recursive way
    void DestroyTree(RankTreeNode* root) {
        if (root == nullptr)
            return;
        DestroyTree(root->LeftSon);
        DestroyTree(root->RightSon);
        delete root;
    }

    
    RankTreeNode *Search(int salary){
        if (this->Root == nullptr) {
            return nullptr;
        }
        RankTreeNode *ptr = this->Root;
        while (ptr != nullptr) {
            if (ptr->salary.salary == salary) {
                return ptr;
            }
            else if (ptr->salary.salary < salary){
                ptr = ptr->RightSon;
            }
            else{
                ptr = ptr->LeftSon;
            }
        }
        return nullptr;
    }

    void SearchAndDelete(int salary, int score){
        if(this->Root == nullptr) {
            return;
        }
        RankTreeNode *ptr = this->Root;
        while (ptr != nullptr) {
            if (ptr->salary.salary == salary) {
                ptr->salary.DeleteEmployee(score);
                return;
            }
            else if (ptr->salary.salary < salary){
                ptr->salary.CoDeleteEmployee(score);
                ptr = ptr->RightSon;
            }
            else{
                ptr->salary.CoDeleteEmployee(score);
                ptr = ptr->LeftSon;
            }
        }
        return;
    }

    void SearchAndAdd(int salary, int score){
        if (this->Root == nullptr) {
            return;
        }
        RankTreeNode *ptr = this->Root;
        while (ptr != nullptr) {
            if (ptr->salary.salary == salary) {
                ptr->salary.AddEmployee(score);
                return;
            }
            else if (ptr->salary.salary < salary){
                ptr->salary.CoAddEmployee(score);
                ptr = ptr->RightSon;
            }
            else{
                ptr->salary.CoAddEmployee(score);
                ptr = ptr->LeftSon;
            }
        }
        return;
    }

    void SearchAndNum(int salary , int &grades,int &num,int &numInsalary,int &GradesInsalary){
        if (this->Root == nullptr) {
            return;
        }
        RankTreeNode *ptr = this->Root;
        while (ptr != nullptr) {
            if(ptr->salary.salary == salary && ptr->LeftSon == nullptr){
                    num += ptr->salary.num;
                    numInsalary = ptr->salary.num;
                    GradesInsalary = ptr->salary.Grades;
                    grades += ptr->salary.Grades;
                    return;
            }
            else if(ptr->salary.salary == salary){
                    num += (ptr->salary.num + ptr->LeftSon->salary.CoTreeNum);
                    numInsalary = ptr->salary.num;
                    GradesInsalary = ptr->salary.Grades;
                    grades += (ptr->salary.Grades += ptr->LeftSon->salary.CoTreeGrades);
                    return;
            }
            else if (ptr->salary.salary < salary && ptr->LeftSon == nullptr ){
                    num += ptr->salary.num;
                    grades += ptr->salary.Grades;
                    ptr = ptr->RightSon;
            }
            else if(ptr->salary.salary < salary){
                    num += (ptr->salary.num + ptr->LeftSon->salary.CoTreeNum);
                    grades += (ptr->salary.Grades += ptr->LeftSon->salary.CoTreeGrades);
                    ptr = ptr->RightSon;
            }
            else if(ptr->salary.salary > salary){
                ptr = ptr->LeftSon;
            }
        }
    }

    void SearchAndSum(int salary ,int &sum){
        if (this->Root == nullptr) {
            return;
        }
        RankTreeNode *ptr = this->Root;
        while (ptr != nullptr) {
            if (ptr->salary.salary == salary){
                if(ptr->LeftSon == nullptr) sum += ptr->salary.Grades;
                else sum += (ptr->salary.Grades + ptr->LeftSon->salary.CoTreeGrades);
                return;
            }
           else if (ptr->salary.salary < salary){
                if(ptr->LeftSon == nullptr) sum += ptr->salary.Grades;
                else sum += (ptr->salary.Grades + ptr->LeftSon->salary.CoTreeGrades);
                ptr = ptr->RightSon;
            }
            else{
                ptr = ptr->LeftSon;
            }
        }
    }

    void SearchAndBumpGrade(int salary, int BumpGrade){
        if (this->Root == nullptr) {
            return;
        }
        RankTreeNode *ptr = this->Root;
        while (ptr != nullptr) {
            if (ptr->salary.salary == salary) {
                ptr->salary.Grades += BumpGrade;
                ptr->salary.CoTreeGrades += BumpGrade;
                return;
            }
            else if (ptr->salary.salary < salary){
                ptr->salary.CoTreeGrades += BumpGrade;
                ptr = ptr->RightSon;
            }
            else{
                ptr->salary.CoTreeGrades += BumpGrade;
                ptr = ptr->LeftSon;
            }
        }
        return;
    }

    
    bool Insert(const Salary& salary){
        if (this->Root == nullptr) {
            this->Root = new RankTreeNode(salary);
            if(this->Root == nullptr) throw std::bad_alloc();
            this->Root->w = 1;
        } else {
            RankTreeNode *p, *son = Root;
            while (true) {
                p = son; /// hold the father in P
                if(son->salary.salary == salary.salary){
                    son->salary += salary;
                    p = son->Parent;
                    while(p != nullptr) {
                        p->w--;
                        p = p->Parent;
                    }
                    return true;   
                }else{ 
                    if(son->salary.salary > salary.salary){
                    son->w += 1;
                    son->salary.CoTreeGrades += salary.Grades;
                    son->salary.CoTreeNum += salary.num;
                    son = son->LeftSon;   
                }else{
                    son->w += 1;
                    son->salary.CoTreeGrades += salary.Grades;
                    son->salary.CoTreeNum += salary.num;
                    son = son->RightSon;
                    }
                }
                    
                if (son == nullptr) {
                    if(p->salary.salary > salary.salary){
                        RankTreeNode* tmp = new RankTreeNode(salary);
                        if(tmp == nullptr) throw std::bad_alloc();
                        p->LeftSon = tmp;
                        p->LeftSon->Parent = p;
                        p->LeftSon->w = 1;
                    }else{
                        RankTreeNode* tmp = new RankTreeNode(salary);
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
        RankTreeNode *ptr1 = this->Root;

        while(ptr1 != nullptr){
            if(ptr1->LeftSon == nullptr) sum += ptr1->salary.Grades;
            else sum += (ptr1->salary.Grades + ptr1->LeftSon->salary.CoTreeGrades);
            ptr1 = ptr1->RightSon;
        }
        return;

    }


    // void deleteNode(RankTreeNode* Node){
    //     if(Node->LeftSon == nullptr && Node->RightSon == nullptr){
    //             if(Node->Parent == nullptr)
    //                 Root = nullptr;
    //             else{
    //                 if(Node->Parent->LeftSon == Node){  
    //                     Node->Parent->LeftSon = nullptr; 
    //                 }else{
    //                     Node->Parent->RightSon = nullptr;
    //                 }    
                
    //                 RankTreeNode* p = Node->Parent;
    //                 while(p != nullptr) {
    //                     p->w--;
    //                     p->salary.CoTreeGrades -= Node->salary.Grades;
    //                     p->salary.CoTreeNum -= Node->salary.num;
    //                     p = p->Parent;
    //                 }
    //             }
    //         delete Node;
    //         return;
    //     }
    //     RankTreeNode *son = Root;
    //     while (true) {       
    //         if(son->salary.salary == Node->salary.salary){
    //             if(Node->LeftSon == nullptr){
    //                 Node->RightSon->Parent = Node->Parent;
    //                 if(Node != Root && Node == Node->Parent->LeftSon) Node->Parent->LeftSon = Node->RightSon; 
    //                 else if(Node != Root && Node == Node->Parent->RightSon) Node->Parent->RightSon = Node->RightSon; 
    //                 if(Node == Root){
    //                     Node->RightSon->Parent = nullptr;
    //                     Root = Node->RightSon;
    //                 }
    //                 delete Node;
    //                 return;
    //             }

    //             if(Node->RightSon == nullptr){
    //                 Node->LeftSon->Parent = Node->Parent;
    //                 if(Node != Root && Node == Node->Parent->LeftSon) Node->Parent->LeftSon = Node->LeftSon; 
    //                 else if(Node != Root && Node == Node->Parent->RightSon) Node->Parent->RightSon = Node->LeftSon; 
    //                 if(Node == Root) {
    //                     Node->LeftSon->Parent = nullptr;
    //                     Root = Node->LeftSon;
    //                 }
    //                 delete Node;
    //                 return;
    //             }
    //         break;
            
    //         }else if(son->salary.salary > Node->salary.salary){
    //             son->w -= 1;
    //             son->salary.CoTreeGrades -= Node->salary.Grades;
    //             son->salary.CoTreeNum -= Node->salary.num;
    //             son = son->LeftSon;
    //         }else{
    //             son->w -= 1;
    //             son->salary.CoTreeGrades -= Node->salary.Grades;
    //             son->salary.CoTreeNum -= Node->salary.num;
    //             son = son->RightSon;
    //         }
    //     }
    //     int flag;
    //     RankTreeNode *Replacement;
    //     if(Node->LeftSon != NULL){
    //         Replacement = son->LeftSon;
    //         while(Replacement->RightSon != nullptr) Replacement = Replacement->RightSon;
    //         flag = 0;
    //     }else{
    //         Replacement = son->RightSon;
    //         while(Replacement->LeftSon != nullptr) Replacement = Replacement->LeftSon;
    //         flag = 1;
    //     }

    //     RankTreeNode *tmp = son;
    //     while (true) {       
    //         if(tmp->salary.salary == Replacement->salary.salary){
    //             son->salary = Replacement->salary;
    //             son->salary.CoTreeNum = son->salary.num;
    //             son->salary.CoTreeGrades = son->salary.Grades;
    //             if(son->LeftSon != nullptr){
    //                 son->salary.CoTreeNum += son->LeftSon->salary.CoTreeNum;
    //                 son->salary.CoTreeGrades += son->LeftSon->salary.CoTreeGrades;
    //             }
    //             if(son->RightSon != nullptr){
    //                 son->salary.CoTreeNum += son->RightSon->salary.CoTreeNum;
    //                 son->salary.CoTreeGrades += son->RightSon->salary.CoTreeGrades;
    //             }
    //             if(flag == 0){
    //                 if(son->LeftSon != Replacement){
    //                     Replacement->Parent->RightSon = Replacement->LeftSon;
    //                 }else{
    //                     Replacement->Parent->LeftSon = Replacement->LeftSon;
    //                 } 
    //                 if(Replacement->LeftSon != nullptr) Replacement->LeftSon->Parent = Replacement->Parent;
                    
    //             }else if(flag == 1){
    //                 if(son->RightSon != Replacement){
    //                     Replacement->Parent->LeftSon = Replacement->RightSon;
    //                 }else{
    //                     Replacement->Parent->RightSon = Replacement->RightSon;
    //                 } 
    //                 if(Replacement->RightSon != nullptr) Replacement->RightSon->Parent = Replacement->Parent;  
                     
    //             }
    //             delete Replacement;
    //             return;
                
    //         }else if(tmp->salary.salary > Replacement->salary.salary){
    //             tmp->w -= 1;
    //             tmp->salary.CoTreeGrades -= (Replacement->salary.Grades);
    //             tmp->salary.CoTreeNum -= Replacement->salary.num;
    //             tmp = tmp->LeftSon;
    //         }else{
    //             tmp->w -= 1;
    //             tmp->salary.CoTreeGrades -= (Replacement->salary.Grades);
    //             tmp->salary.CoTreeNum -= Replacement->salary.num;
    //             tmp = tmp->RightSon;
    //         }
    //     }
    // }

    // void DeleteFromTree(int salary){
    //     RankTreeNode* Node = Search(salary);
    //     if(Node != nullptr) deleteNode(Node);
    // }


    RankTreeNode* maxNode(RankTreeNode* root){
        RankTreeNode* p = Root;
        while(p->RightSon != nullptr) p = p->RightSon;
        return p;
    }

    RankTreeNode* minNode(RankTreeNode* root ){
        RankTreeNode* p = Root;
        while(p->LeftSon != nullptr) p = p->LeftSon;
        return p;
    }
    
    
    
    RankTreeNode* Select_rank(RankTreeNode* ptr,int Rank) {
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

    RankTreeNode* Select(RankTreeNode* root,int k, int &numInsalary) {

        if(root->RightSon != nullptr){
            if( k <= root->RightSon->salary.CoTreeNum){
                return Select(root->RightSon, k , numInsalary);
            }
            else if(root->salary.num >= (k - root->RightSon->salary.CoTreeNum)){
                numInsalary = (k - root->RightSon->salary.CoTreeNum);
                return root;
            }else if(root->LeftSon != nullptr){
                    return Select(root->LeftSon, k - root->RightSon->salary.CoTreeNum - root->salary.num, numInsalary);
                }
        }

        if(root->salary.num >= k){
            numInsalary = k;
            return root;
        }else{
            if(root->LeftSon != nullptr)
                return Select(root->LeftSon, k - root->salary.num, numInsalary);
        }
        return nullptr;
    }




    void PostOrder(RankTreeNode *node){
        if(node == nullptr)
            return;

        PostOrder(node->LeftSon);
        PostOrder(node->RightSon);

        if(node->RightSon == nullptr && node->LeftSon == nullptr){
            node->w = 1;
            node->salary.CoTreeNum = node->salary.num;
            node->salary.CoTreeGrades = node->salary.Grades;
            
        }
        if(node->RightSon == nullptr && node->LeftSon != nullptr){
            node->w  = node->LeftSon->w + 1;
            node->salary.CoTreeNum = node->LeftSon->salary.CoTreeNum + node->salary.num;
            node->salary.CoTreeGrades = (node->LeftSon->salary.CoTreeGrades + node->salary.Grades);
 
            
        }
        if(node->RightSon != nullptr && node->LeftSon == nullptr){
            node->w  = node->RightSon->w + 1;
            node->salary.CoTreeNum = node->RightSon->salary.CoTreeNum + node->salary.num;
            node->salary.CoTreeGrades = (node->RightSon->salary.CoTreeGrades + node->salary.Grades);

        }
        if(node->RightSon != nullptr && node->LeftSon != nullptr){
            node->w  = node->RightSon->w +  node->LeftSon->w + 1;
            node->salary.CoTreeNum = node->LeftSon->salary.CoTreeNum + node->RightSon->salary.CoTreeNum +node->salary.num;
            node->salary.CoTreeGrades = (node->LeftSon->salary.CoTreeGrades + node->RightSon->salary.CoTreeGrades + node->salary.Grades);
        }
    }


    int MergeSortedArrays(RankTreeNode** array1,RankTreeNode** array2,RankTreeNode** array3,int n1,int n2){
        int i=0,j=0,k=0;
        while (i<n1 && j<n2){
            if(array1[i]->salary.salary < array2[j]->salary.salary)
                array3[k++] = array1[i++];
            else if(array1[i]->salary.salary > array2[j]->salary.salary)
                array3[k++] = array2[j++];
            else{
                array1[i]->salary.EmployeesRank->Root = array1[i]->salary.EmployeesRank->MergeRankTrees(&array1[i]->salary.EmployeesRank->Root, &array2[j]->salary.EmployeesRank->Root, array1[i]->salary.num, array2[j]->salary.num);
                array1[i]->salary += array2[j]->salary;
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

    RankTreeNode* FromArrayToTree(RankTreeNode** array,int start,int end){
        if(start>end)
            return nullptr;
        int mid= (start+end)/2;
        RankTreeNode* root = new RankTreeNode(array[mid]->salary);
        if(root == nullptr) throw std::bad_alloc();
        root->LeftSon =  FromArrayToTree(array,start,mid-1);
        root->RightSon = FromArrayToTree(array,mid+1,end);
        return root;
    }


    int FromTreeToArray(RankTreeNode** array,RankTreeNode* node,int index){
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

    void FixParent(RankTreeNode* root) {
        if(!root)
            return;
        FixParent(root->LeftSon);
        if(root->RightSon)
            root->RightSon->Parent=root;
        if(root->LeftSon)
            root->LeftSon->Parent=root;
        FixParent(root->RightSon);
    }

    RankTreeNode* MergeRankTrees(RankTreeNode** tree1,RankTreeNode** tree2, int size1 , int size2){
        RankTreeNode** array_Of_tree1 = new RankTreeNode*[size1];
        RankTreeNode** array_Of_tree2 = new RankTreeNode*[size2];
        for(int i = 0; i < size1; i++){
            array_Of_tree1[i] = nullptr;
        }
        for(int j = 0; j < size2; j++){
            array_Of_tree2[j] = nullptr;
        }
        FromTreeToArray(array_Of_tree1,*tree1,0);
        FromTreeToArray(array_Of_tree2,*tree2,0);
        
        RankTreeNode** Merged_array = new RankTreeNode*[size1+size2];
        for(int i = 0; i < size1+size2; i++){
            Merged_array[i] = nullptr;
        }
        if(array_Of_tree1 == nullptr || array_Of_tree2 == nullptr || Merged_array == nullptr) throw std::bad_alloc();
        
    
        int k = MergeSortedArrays(array_Of_tree1,array_Of_tree2,Merged_array,size1,size2);
        

        RankTreeNode* root=FromArrayToTree(Merged_array,0, k - 1);
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


#endif //RANKTREE_H
