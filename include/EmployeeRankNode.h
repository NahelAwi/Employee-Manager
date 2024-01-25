
#ifndef EMPLOYEERANKNODE_H
#define EMPLOYEERANKNODE_H


class Employee {
public:
    int employeeId;
    int CoTreeGrade;
    int Grade;
   
    Employee(int employeeId, int grade) : 
        employeeId(employeeId),
        CoTreeGrade(grade),
        Grade(grade)
    {}

    // Employee& operator+=(const Employee& s){
    //     CoTreeGrade += s.CoTreeGrade;
    //     Grade += s.Grade;
    //     return *this;
    // }

};

class EmployeeRankNode {
public:
    Employee employee;
    EmployeeRankNode *Parent;
    EmployeeRankNode *RightSon;
    EmployeeRankNode *LeftSon;
    int w;

    EmployeeRankNode(const Employee& employee , EmployeeRankNode *Parent = nullptr , EmployeeRankNode *RightSon = nullptr,
                 EmployeeRankNode *LeftSon = nullptr , int w = 1  ):
            employee(employee),Parent(Parent),RightSon(RightSon),LeftSon(LeftSon),w(1){

    }
    // EmployeeRankNode(EmployeeRankNode *Parent = nullptr , EmployeeRankNode *RightSon = nullptr, EmployeeRankNode *LeftSon = nullptr , int w = 1  ):
    //         employee(),Parent(Parent),RightSon(RightSon),LeftSon(LeftSon),w(1){

    // }
    ~EmployeeRankNode() = default;
};


#endif //EMPLOYEERANKNODE_H
