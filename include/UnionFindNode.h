
#ifndef UNION_FIND_NODE_H
#define UNION_FIND_NODE_H

#include "RankTree.h"

class UnionFindNode{
public:
    Salary* SalaryZero;
    RankTree* Salaries;
    int EmployeesInCompany;
    double CompanyValue;
    double RelativeValue;

    UnionFindNode(double i){
        Salaries = new RankTree();
        SalaryZero = new Salary(0);
        if(Salaries == nullptr || SalaryZero == nullptr) throw std::bad_alloc();
        EmployeesInCompany = 0;
        CompanyValue = i;
        RelativeValue = 0;
    }

	~UnionFindNode(){
		delete Salaries;
		delete SalaryZero;
	}
    

};


#endif //UNION_FIND_NODE_H
