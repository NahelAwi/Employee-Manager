#include "../include/EmployeesManager.h"
#include "../include/library2.h"




void *Init(int k){
    EmployeesManager *DS = new EmployeesManager(k);
    return (void*)DS;
}

StatusType AcquireCompany(void *DS, int companyID1, int companyID2, double factor){
    if(DS == nullptr) return INVALID_INPUT;
    return ((EmployeesManager*)DS)->AcquireCompany(companyID1, companyID2, factor);
}

StatusType AddEmployee(void *DS, int employeeID, int companyID, int grade){
    if(DS == nullptr) return INVALID_INPUT;
    return ((EmployeesManager*)DS)->addEmployee(employeeID, companyID, grade);
}

StatusType RemoveEmployee(void *DS, int employeeID){
    if(DS == nullptr) return INVALID_INPUT;
    return ((EmployeesManager*)DS)->removeEmployee(employeeID);

}

StatusType EmployeeSalaryIncrease(void *DS, int employeeID, int salaryIncrease){
    if(DS == nullptr) return INVALID_INPUT;
    return ((EmployeesManager*)DS)->employeeSalaryIncrease(employeeID, salaryIncrease);

}

StatusType PromoteEmployee(void *DS, int employeeID, int bumpGrade){
    if(DS == nullptr) return INVALID_INPUT;
    return ((EmployeesManager*)DS)->promoteEmployee(employeeID, bumpGrade);
}


StatusType SumOfBumpGradeBetweenTopWorkersByGroup(void *DS, int companyID, int m){
    if(DS == nullptr) return INVALID_INPUT;
    return ((EmployeesManager*)DS)->sumOfBumpGradeBetweenTopWorkersByGroup(companyID, m);
}

StatusType AverageBumpGradeBetweenSalaryByGroup(void *DS, int companyID, int lowerSalary, int higherSalary){
    if(DS == nullptr) return INVALID_INPUT;
    return ((EmployeesManager*)DS)->averageBumpGradeBetweenSalaryByGroup(companyID, lowerSalary, higherSalary);
}

StatusType CompanyValue(void *DS, int CompanyID){
    if(DS == nullptr) return INVALID_INPUT;
    return ((EmployeesManager*)DS)->companyValue(CompanyID);
}

void Quit(void** DS){
	delete (EmployeesManager*)*DS;
    *DS = nullptr;    
}
