#ifndef Employee_MANAGER_H
#define Employee_MANAGER_H

#include "HashTable.h"
#include "UnionFind.h"
#include "RankTree.h"
#include "library2.h"
#include "cassert"
#include <stdexcept>

class EmployeesManager{
public:
    
    RankTree Salaries;
    Salary SalaryZero;
    UnionFind Companies;
    HashTable Employees;
    int NumOfCompanies;
    

    EmployeesManager(int NumOfCompanies) :  Salaries(), SalaryZero(0),
                                                    Companies(NumOfCompanies), Employees(), NumOfCompanies(NumOfCompanies){
                         
    }
    ~EmployeesManager() = default;

    StatusType AcquireCompany(int AcquirerID, int TargetID, double factor){
        if(AcquirerID <= 0 || AcquirerID > NumOfCompanies || TargetID <= 0 || TargetID > NumOfCompanies || TargetID == AcquirerID || factor <= 0.0) return INVALID_INPUT;
        try{
            UnionFindNode* Company1 = Companies.find2(AcquirerID);
            UnionFindNode* Company2 = Companies.find2(TargetID);
            if (Companies.CompanySizes[Companies.find1(AcquirerID)] >= Companies.CompanySizes[Companies.find1(TargetID)]){
                for(int i = 0 ; i < Employees.size; i++){
                    HashTableEntry* Employee = Employees.table[i].Next;
                    while(Employee != nullptr){
                        if(Employee->Company == Company2)
                            Employee->Company = Company1;
                        Employee = Employee->Next;
                    }
                }
            }else{
                for(int i = 0 ; i < Employees.size; i++){
                    HashTableEntry* Employee = Employees.table[i].Next;
                    while(Employee != nullptr){
                        if(Employee->Company == Company1)
                            Employee->Company = Company2;
                        Employee = Employee->Next;
                    }
                }
            }
            Companies.Union(AcquirerID, TargetID, factor);
            
        }catch(std::bad_alloc const&){
            return ALLOCATION_ERROR;
        }
        return SUCCESS;
    }

    StatusType addEmployee( int EmployeeID, int CompanyID, int grade){
        if(CompanyID <= 0 || CompanyID > NumOfCompanies || EmployeeID <= 0 || grade < 0) return INVALID_INPUT;
        try{
            UnionFindNode* Company = Companies.find2(CompanyID);
            if(Employees.add(EmployeeID, 0, grade, Company) == false) return FAILURE;
            HashTableEntry* Employee = Employees.SearchEmployeeID(EmployeeID);
            Employee->Company = Company;

            SalaryZero.AddEmployee(grade);
            Company->SalaryZero->AddEmployee(grade);
            Company->EmployeesInCompany++;
        }catch(std::bad_alloc const&){
            return ALLOCATION_ERROR;
        }
        return SUCCESS;
    }

    StatusType removeEmployee(int EmployeeID){
        if(EmployeeID <= 0) return INVALID_INPUT;
        UnionFindNode* Company = Employees.find(EmployeeID);
        if(Company == nullptr) return FAILURE;
        if(Company->EmployeesInCompany > 0) Company->EmployeesInCompany--;
        HashTableEntry* Employee = Employees.SearchEmployeeID(EmployeeID);
        if(Employee->salary != 0){
            //if (Company->Salaries->Search(Employee->Salary)->Salary.num == 1){
            //    Company->Salaries->DeleteFromTree(Employee->Salary);
            //}else{
                
                Company->Salaries->SearchAndDelete(Employee->salary, Employee->grade);
                Company->Salaries->Search(Employee->salary)->salary.EmployeesRank->DeleteFromTree(EmployeeID);
            //}
            //if (Salaries.Search(Employee->Salary)->Salary.num == 1){
            //    Salaries.DeleteFromTree(Employee->Salary);
            //}else{
                Salaries.SearchAndDelete(Employee->salary,Employee->grade);
                Salaries.Search(Employee->salary)->salary.EmployeesRank->DeleteFromTree(EmployeeID);
            //}
            
        }else{
            Company->SalaryZero->DeleteEmployee(Employee->grade);
            SalaryZero.DeleteEmployee(Employee->grade);
        }
        Employees.remove(EmployeeID);
        
        return SUCCESS;
    }



    StatusType employeeSalaryIncrease(int EmployeeID, int SalaryIncrease){
        if(EmployeeID <= 0 || SalaryIncrease <= 0) return INVALID_INPUT;
        UnionFindNode* Company = Employees.find(EmployeeID);
        if(Company == nullptr) return FAILURE;
        HashTableEntry* employee = Employees.SearchEmployeeID(EmployeeID);
        
        if(employee->salary != 0){
            //if (Company->Salaries->Search(Employee->Salary)->Salary.num <= 1){
            //    Company->Salaries->DeleteFromTree(Employee->Salary);
            //}else{
                Company->Salaries->SearchAndDelete(employee->salary,employee->grade);
                Company->Salaries->Search(employee->salary)->salary.EmployeesRank->DeleteFromTree(EmployeeID);
            //}
            //if (Salaries.Search(Employee->Salary)->Salary.num <= 1){
            //    Salaries.DeleteFromTree(Employee->Salary);
            //}else{
                Salaries.SearchAndDelete(employee->salary,employee->grade);
                Salaries.Search(employee->salary)->salary.EmployeesRank->DeleteFromTree(EmployeeID);
            //}
        }else{
            Company->SalaryZero->DeleteEmployee(employee->grade);
            SalaryZero.DeleteEmployee(employee->grade);
        }
        employee->salary += SalaryIncrease;

        try{
            Salary tmp(employee->salary);
            Employee new_employee(EmployeeID, employee->grade);
            tmp.AddEmployee(employee->grade);
            Salaries.Insert(tmp);
            Salaries.Search(employee->salary)->salary.EmployeesRank->Insert(new_employee);
            Company->Salaries->Insert(tmp);
            Company->Salaries->Search(employee->salary)->salary.EmployeesRank->Insert(new_employee);
        }catch(std::bad_alloc const&){
            return ALLOCATION_ERROR;
        }

        return SUCCESS;
    }

    StatusType promoteEmployee(int EmployeeID, int BumpGrade){
        if(EmployeeID <= 0) return INVALID_INPUT;
        UnionFindNode* Company = Employees.find(EmployeeID);
        if(Company == nullptr) return FAILURE;
        if(BumpGrade <= 0) return SUCCESS;
        HashTableEntry* employee = Employees.SearchEmployeeID(EmployeeID);
        Employee new_employee(EmployeeID, employee->grade + BumpGrade);
        if(employee->salary != 0){
            Company->Salaries->SearchAndBumpGrade(employee->salary, BumpGrade);
            Salaries.SearchAndBumpGrade(employee->salary, BumpGrade);
            Company->Salaries->Search(employee->salary)->salary.EmployeesRank->DeleteFromTree(EmployeeID);
            Company->Salaries->Search(employee->salary)->salary.EmployeesRank->Insert(new_employee);
            Salaries.Search(employee->salary)->salary.EmployeesRank->DeleteFromTree(EmployeeID);
            Salaries.Search(employee->salary)->salary.EmployeesRank->Insert(new_employee);
        }else{
            Company->SalaryZero->Grades += BumpGrade;
            Company->SalaryZero->CoTreeGrades += BumpGrade;

            SalaryZero.Grades += BumpGrade;
            SalaryZero.CoTreeGrades += BumpGrade;
        }
        employee->grade += BumpGrade;

        return SUCCESS;
    }


    StatusType averageBumpGradeBetweenSalaryByGroup( int CompanyID, int lowerSalary, int higherSalary){
        if(CompanyID < 0 || CompanyID > NumOfCompanies || lowerSalary < 0 || higherSalary < 0 || lowerSalary > higherSalary) return INVALID_INPUT;
        double AllSum = 0;
        double Allgrades = 0;
        if(CompanyID == 0){
            if(lowerSalary == higherSalary){
                if(lowerSalary != 0){
                    RankTreeNode* node = Salaries.Search(lowerSalary);
                    if(node == nullptr || node->salary.num == 0) return FAILURE;
                    printf("averageBumpGradeBetweenSalaryByGroup: %.1f\n", ((double)node->salary.Grades/(double)node->salary.num));
                    return SUCCESS;
                }else{
                    if(SalaryZero.num == 0) return FAILURE;
                    printf("averageBumpGradeBetweenSalaryByGroup: %.1f\n", ((double)SalaryZero.Grades/(double)SalaryZero.num));
                    return SUCCESS;
                }
            }
            GetPercentageHelp(&Salaries, lowerSalary, higherSalary, AllSum, Allgrades);
            if(lowerSalary <= 0){
                AllSum += SalaryZero.num;
                Allgrades += SalaryZero.Grades;
            }
            if(AllSum <= 0) return FAILURE;
            printf("averageBumpGradeBetweenSalaryByGroup: %.1f\n", (Allgrades/AllSum));
            
        }else{
            
            UnionFindNode * Company = Companies.find2(CompanyID);
            if(lowerSalary == higherSalary){
                if(lowerSalary != 0){
                    RankTreeNode* node = Company->Salaries->Search(lowerSalary);
                    if(node == nullptr || node->salary.num == 0) return FAILURE;
                    printf("averageBumpGradeBetweenSalaryByGroup: %.1f\n", ((double)node->salary.Grades/(double)node->salary.num));
                    return SUCCESS;
                }else{
                    if(Company->SalaryZero->num == 0) return FAILURE;
                    printf("averageBumpGradeBetweenSalaryByGroup: %.1f\n", ((double)Company->SalaryZero->Grades/(double)Company->SalaryZero->num));
                    return SUCCESS;
                }
            }
            GetPercentageHelp(Company->Salaries, lowerSalary, higherSalary, AllSum, Allgrades);
            if(lowerSalary <= 0){
                AllSum += Company->SalaryZero->num ;
                Allgrades += Company->SalaryZero->Grades;
            }
            if(AllSum <= 0) return FAILURE;
            printf("averageBumpGradeBetweenSalaryByGroup: %.1f\n", (Allgrades/AllSum));
        }
        return SUCCESS;
    }


    void GetPercentageHelp(RankTree *tree, int lowerSalary, int higherSalary, double& AllSum, double& Allgrades){
        int SumToLowerSalary = 0;
        int gradesToLowerSalary = 0;
        int SumToHigherSalary = 0;
        int gradesToHigherSalary = 0;
        int LowerSalaryNum = 0;
        int LowerSalariegrade = 0;
        int HigherSalaryNum = 0;
        int HigherSalariegrade = 0;
        tree->SearchAndNum(lowerSalary, gradesToLowerSalary, SumToLowerSalary, LowerSalaryNum, LowerSalariegrade);
        tree->SearchAndNum(higherSalary, gradesToHigherSalary, SumToHigherSalary, HigherSalaryNum, HigherSalariegrade);
        AllSum = SumToHigherSalary - SumToLowerSalary + LowerSalaryNum;
        Allgrades = gradesToHigherSalary - gradesToLowerSalary + LowerSalariegrade;
    }



    
    StatusType sumOfBumpGradeBetweenTopWorkersByGroup(int CompanyID, int m){
        if(CompanyID < 0 || CompanyID > NumOfCompanies || m <=0 ) return INVALID_INPUT;
        int SumToMax = 0;
        int SumToSalary = 0;
        int numInSalary = 0;
        if(CompanyID == 0){
            if(Salaries.Root == nullptr){
                if(m > 0) return FAILURE;
                printf("sumOfBumpGradeBetweenTopWorkersByGroup: %d\n", 0);
                return SUCCESS;
            }
            if(m > (Salaries.Root->salary.CoTreeNum)) return FAILURE;
            RankTreeNode *node;
            Salaries.GetRightestSum(SumToMax);
            if( m <= Salaries.Root->salary.CoTreeNum){     ////////////////////
                node = Salaries.Select(Salaries.Root, m, numInSalary);
                if(node == nullptr) {
                    printf("sumOfBumpGradeBetweenTopWorkersByGroup: %d\n", SumToMax);
                    return SUCCESS;
                }
                
                Salaries.SearchAndSum(node->salary.salary, SumToSalary);
                EmployeeRankNode* tmp = node->salary.EmployeesRank->Select_rank(node->salary.EmployeesRank->Root, node->salary.num - numInSalary + 1);
                int EmployeesSumToMax = 0;
                int EmployeesSumToTmp = 0;
                node->salary.EmployeesRank->SearchAndSum(tmp->employee.employeeId, EmployeesSumToTmp);
                node->salary.EmployeesRank->GetRightestSum(EmployeesSumToMax);
                
                int finalResult = EmployeesSumToMax - EmployeesSumToTmp + tmp->employee.Grade;
                printf("sumOfBumpGradeBetweenTopWorkersByGroup: %d\n", (SumToMax - SumToSalary + finalResult));
            }else{
                printf("sumOfBumpGradeBetweenTopWorkersByGroup: %d\n", SumToMax );
            } 
        }else{
            UnionFindNode * Company = Companies.find2(CompanyID);
            if(Company->Salaries->Root == nullptr){
                if(m > 0) return FAILURE;
                printf("sumOfBumpGradeBetweenTopWorkersByGroup: %d\n", 0);
                return SUCCESS;
            }
            if(m > Company->EmployeesInCompany) return FAILURE;
            RankTreeNode *SalaryInCompany;
            Company->Salaries->GetRightestSum(SumToMax);
            if(m <= Company->Salaries->Root->salary.CoTreeNum){      //////////////////
                SalaryInCompany = Company->Salaries->Select(Company->Salaries->Root, m, numInSalary);
                if(SalaryInCompany == nullptr) {
                    printf("sumOfBumpGradeBetweenTopWorkersByGroup: %d\n", SumToMax);
                    return SUCCESS;
                }
                Company->Salaries->SearchAndSum(SalaryInCompany->salary.salary, SumToSalary);
                EmployeeRankNode* tmp = SalaryInCompany->salary.EmployeesRank->Select_rank(SalaryInCompany->salary.EmployeesRank->Root, SalaryInCompany->salary.num - numInSalary + 1);
                int EmployeesSumToMax = 0;
                int EmployeesSumToTmp = 0;
                SalaryInCompany->salary.EmployeesRank->SearchAndSum(tmp->employee.employeeId, EmployeesSumToTmp);
                SalaryInCompany->salary.EmployeesRank->GetRightestSum(EmployeesSumToMax);
                int finalResult = EmployeesSumToMax - EmployeesSumToTmp + tmp->employee.Grade;
                printf("sumOfBumpGradeBetweenTopWorkersByGroup: %d\n", (SumToMax - SumToSalary + finalResult));
            }else{
                printf("sumOfBumpGradeBetweenTopWorkersByGroup: %d\n", SumToMax);
            }
        }
        return SUCCESS;
    }



    StatusType companyValue(int CompanyID){
        if(CompanyID < 0 || CompanyID > NumOfCompanies) return INVALID_INPUT;
        printf("companyValue: %f\n", Companies.CalculateCompanyValue(CompanyID));
        return SUCCESS;

    }
    // void printEmployeesInSalary(RankTreeNode* root){
    //     if(root == nullptr) return;
        
    //     //std::cout << root->Salary.Salary << " " << root->Salary.num << " " << root->Salary.CoTreeNum << " " << root->Salary.CoTreeSum << std::endl;
    //     std::cout << "Salary IS:  " << root->Salary.Salary << "  NUM IN THAT Salary:" << root->Salary.num << std::endl;
    //     for(int i = 1; i < scale; i++){
    //         //std::cout << i << " " << "TREE :  "<< SalaryZero.grades[i] << "CO TREE :  "<< SalaryZero.CoTreegrades[i] << std::endl;
    //         if (root->Salary.CoTreegrades[i] != 0) std::cout << i << " " << "TREE :  "<< root->Salary.grades[i] << "CO TREE :  "<< root->Salary.CoTreegrades[i] << std::endl;
    //         //std::cout << root->Salary.CoTreegrades[i] << std::endl;
    //     }
    //     printEmployeesInSalary(root->LeftSon);   
    //     printEmployeesInSalary(root->RightSon);
        
    // }

   /* 
    void display() {
        for (int i = 0; i < Employees.size; i++) {
            int v= Employees.table[i].EmployeeID;
            if (!v)
                std::cout <<"Position: "<<i<<" ID: Null  "<< "MATSAV: " << Employees.table[i].info << "Salary: "<< Employees.table[i].Salary << "grade: "<< Employees.table[i].grade <<std::endl;
            else
                std::cout<<"Position: "<<i<<" ID: "<<v <<"    "<< "MATSAV: " << Employees.table[i].info << "Salary: "<< Employees.table[i].Salary << "grade: "<< Employees.table[i].grade <<std::endl;
        }
    }
    */

};

#endif