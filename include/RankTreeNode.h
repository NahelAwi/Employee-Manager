
#ifndef RANKTREENODE_H
#define RANKTREENODE_H

#include "EmployeeRankTree.h"


class Salary {
public:
    int salary;
    int num;
    int CoTreeNum;
    int CoTreeGrades;
    int Grades;
    EmployeeRankTree* EmployeesRank;
    

    
    Salary(int salary = 0, int num = 0, int CoTreeNum = 0, int CoTreeGrades = 0, int Grades = 0) : salary(salary) , num(num), CoTreeNum(CoTreeNum), CoTreeGrades(CoTreeGrades), Grades(Grades) {
        EmployeesRank = new EmployeeRankTree();
    }

    
    
    // Salary(const Salary& s){
    //     salary = s.salary;
    //     num = s.num;
    //     CoTreeGrades = s.CoTreeGrades;
    //     CoTreeNum = s.CoTreeNum;
    //     Grades = s.Grades;
    //     EmployeesRank = s.EmployeesRank;
    // }
    Salary(const Salary& s) = delete;
    Salary& operator=(const Salary& s) = delete;
    // Salary& operator=(const Salary& s){
    //     salary = s.salary;
    //     num = s.num;
    //     CoTreeGrades = s.CoTreeGrades;
    //     CoTreeNum = s.CoTreeNum;
    //     Grades = s.Grades;
    //     EmployeesRank = s.EmployeesRank;
       
    //     return *this;
    // }

    Salary& operator+=(const Salary& s){
        num += s.num;
        CoTreeNum += s.CoTreeNum;
        CoTreeGrades += s.CoTreeGrades;
        Grades += s.Grades;
        
        return *this;
    }

    void AddEmployee(int grade){
        num++;
        CoTreeNum++;
        CoTreeGrades += grade;
        Grades += grade;
        
    }

    void CoAddEmployee(int grade){
        CoTreeNum++;
        CoTreeGrades += grade;

    }

    void DeleteEmployee(int grade){
        num--;
        CoTreeNum--;
        CoTreeGrades -= grade;
        Grades -= grade;
    }

    void CoDeleteEmployee(int grade){
        CoTreeNum--;
        CoTreeGrades -= grade;
    }
    
    ~Salary(){
        delete EmployeesRank;
    }

};

class RankTreeNode {
public:
    Salary salary;
    RankTreeNode *Parent;
    RankTreeNode *RightSon;
    RankTreeNode *LeftSon;
    //int BalanceFactor;
    //int height;
    int w;

    RankTreeNode(const Salary& salary , RankTreeNode *Parent = nullptr , RankTreeNode *RightSon = nullptr,
                 RankTreeNode *LeftSon = nullptr , int w = 1  ):
            salary(salary.salary, salary.num,salary.CoTreeNum, salary.CoTreeGrades,salary.Grades),
            Parent(Parent),RightSon(RightSon),LeftSon(LeftSon),w(1){

    }
    RankTreeNode(RankTreeNode *Parent = nullptr , RankTreeNode *RightSon = nullptr, RankTreeNode *LeftSon = nullptr , int w = 1  ):
            salary(),Parent(Parent),RightSon(RightSon),LeftSon(LeftSon),w(1){

    }
    ~RankTreeNode() = default;
};


#endif //RANKTREENODE_H
