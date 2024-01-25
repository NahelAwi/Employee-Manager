

#ifndef UNIONFIND_H
#define UNIONFIND_H

#include "UnionFindNode.h"

class UnionFind {
public:
    int NumOfCompanies;
    int* CompaniesParents;
    int* CompanySizes; // how many Companies in the union find
    UnionFindNode** Companies; // contain the elements

    UnionFind(int NumOfCompanies): NumOfCompanies(NumOfCompanies){
        CompaniesParents = new int[NumOfCompanies + 1];
        CompanySizes = new int[NumOfCompanies + 1];
        Companies = new UnionFindNode*[NumOfCompanies+ 1];
        if(CompaniesParents == nullptr || CompanySizes == nullptr || Companies == nullptr) throw std::bad_alloc();
        for(int i = 0 ; i <= NumOfCompanies ; i++){
            CompaniesParents[i] = i;
            CompanySizes[i] = 1;
            Companies[i] = new UnionFindNode((double)i);
            if(Companies[i] == nullptr) throw std::bad_alloc();
        }
    }

    ~UnionFind(){
        for(int i = 0 ; i <= NumOfCompanies ; i++){
            if(Companies[i] == nullptr)
                continue;
            //delete Companies[i]->Salaries;
            //Companies[i]->Salaries = nullptr;
            //delete Companies[i]->SalaryZero;
            //Companies[i]->SalaryZero = nullptr;
            delete Companies[i];
            Companies[i] = nullptr;
        }
        delete[] Companies;
        delete[] CompaniesParents;
        delete[] CompanySizes;
    }


    int find1(int group_ID){
        int root = group_ID;
        int parent = 0;
        double sumRelativeValues = 0;
        while (root != CompaniesParents[root]){
            sumRelativeValues += Companies[root]->RelativeValue;
            root = CompaniesParents[root];
        }
        if(root == group_ID)
            return root;

        while(group_ID != CompaniesParents[group_ID]){ // kevotz
            parent = CompaniesParents[group_ID];

            double temp = Companies[group_ID]->RelativeValue;
            Companies[group_ID]->RelativeValue = sumRelativeValues;
            sumRelativeValues -= temp;
            
            CompaniesParents[group_ID] = root;
            group_ID = parent;
        }
        return root;
    }



    UnionFindNode* find2(int group_id){
        int root = group_id;
        int parent = 0;
        double sumRelativeValues = 0;
        while (root != CompaniesParents[root]){
            sumRelativeValues += Companies[root]->RelativeValue;
            root = CompaniesParents[root];
        }
        if(root == group_id)
            return Companies[root];

        while(group_id != CompaniesParents[group_id]){ // kevotz
            parent = CompaniesParents[group_id];
            
            double temp = Companies[group_id]->RelativeValue;
            Companies[group_id]->RelativeValue = sumRelativeValues;
            sumRelativeValues -= temp;
            
            CompaniesParents[group_id] = root;
            group_id = parent;
        }
        return Companies[root];
    }


    int Union(int AcquirerID,int TargetID, double factor){
        int Father1 = this->find1(AcquirerID);
        int Father2 = this->find1(TargetID);
        if(Father1 == Father2)
            return Father1;

        int bigger_group = Father1; //(CompanySizes[Father1] >= CompanySizes[Father2]) ? Father1 : Father2 ;
        int smallest_group = Father2; //(CompanySizes[Father1] < CompanySizes[Father2]) ? Father1 : Father2 ;
        
        CompanySizes[bigger_group] = CompanySizes[Father1] +CompanySizes[Father2];
        RankTreeNode *group1Root = Companies[Father1]->Salaries->Root;
        RankTreeNode *group2Root = Companies[Father2]->Salaries->Root;
        int group2Size = 0;
        int group1Size = 0;
        if(Companies[Father1]->Salaries->Root == nullptr){
            group1Size = 0;
        }else{
            group1Size = Companies[Father1]->Salaries->Root->w;
        }
        
        if(Companies[Father2]->Salaries->Root == nullptr){
             group2Size = 0;
        }else{
             group2Size = Companies[Father2]->Salaries->Root->w;
        }
        //if(Companies[bigger_group] == Companies[smallest_group]) std::cout << "   " << (Companies[bigger_group]->SalaryZero->num) << "    " << (Companies[smallest_group]->SalaryZero->num) << "   ";
        
        (*Companies[bigger_group]->SalaryZero) += (*Companies[smallest_group]->SalaryZero);
        
        Companies[bigger_group]->Salaries->Root = Companies[bigger_group]->Salaries->MergeRankTrees(&group1Root,&group2Root,group1Size,group2Size);
        

        if(bigger_group == Father1){
            CompaniesParents[Father2] = bigger_group;
            CompanySizes[Father2] = 0;
            Companies[Father1]->EmployeesInCompany += Companies[Father2]->EmployeesInCompany;

            Companies[Father1]->CompanyValue += Companies[Father2]->CompanyValue * factor;
            Companies[Father2]->RelativeValue = Companies[Father2]->CompanyValue - Companies[Father1]->CompanyValue;
            //delete Companies[Father2]->SalaryZero;
            Companies[Father2]->Salaries->Root = nullptr;
            //delete Companies[Father2];
            //Companies[Father2] = nullptr;//Companies[Father1];
        }/*else{
            CompaniesParents[Father1] = bigger_group;
            CompanySizes[Father1] = 0;
            Companies[Father2]->EmployeesInCompany += Companies[Father1]->EmployeesInCompany;
            //delete Companies[Father1]->SalaryZero;
            Companies[Father1]->Salaries->Root = nullptr;
            delete Companies[Father1];
            Companies[Father1] = nullptr;//Companies[Father2];
        }*/

        return bigger_group;
    }

    double CalculateCompanyValue(int CompanyID){
        int root = CompanyID;
        double sumRelativeValues = 0;
        while (root != CompaniesParents[root]){
            sumRelativeValues += Companies[root]->RelativeValue;
            root = CompaniesParents[root];
        }
        return (sumRelativeValues + Companies[root]->CompanyValue);
    }


};


#endif //UNIONFIND_H
