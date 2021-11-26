-- LANGUAGE: psql
-- a. Consider the employee data.
-- Employee (employee-id, employee-name, street, city)
-- Works (employee-name, company-name, salary)
-- Company (company-name, city)
-- Manages (employee-name, manager-name)
-- (i) Find the name of all employees who work for State Bank of India.
-- (ii) Find the names and cities of residence of all employees who work for State Bank of India.
-- (iii) Create a view for employee based on salary in ascending order.
-- (iv) Find all employees in the database who earn more than every employee of UCO Bank.
-- (v) Find the employee in the database who earn minimum in state bank of India
-- (vi) Create a Function that displays the employee who earn maximum in SBI.
-- (vii) Write a procedure which takes the city as input parameter and lists the names of all
-- employees belonging to that city.
-- (viii) Write a function that will display the number of employees with salary more than 50k.
-- (ix) Write a procedure raise_sal which increases the salary of an employee. It accepts an
-- employee number and salary increase amount.
-- (x) Create a Procedure that displays the details of managers working in a bank
--
--
--
--
-- Employee
drop table if exists Employee cascade;
CREATE TABLE Employee(
    empid INT NOT NULL,
    empname VARCHAR(50) NOT NULL,
    street VARCHAR(150) NOT NULL,
    city VARCHAR(150) NOT NULL,
    PRIMARY KEY (empid)
);
--  Company
drop table if exists Company cascade;
CREATE TABLE Company(
    companyname VARCHAR(50) NOT NULL,
    city VARCHAR(50) NOT NULL,
    PRIMARY KEY (companyname, city)
);
-- Works
drop table if exists Works cascade;
CREATE TABLE Works(
    empname VARCHAR(50) NOT NULL,
    companyname VARCHAR(50) NOT NULL,
    salary INT NOT NULL,
    PRIMARY KEY (empname, companyname)
);
-- Manages
drop table if exists Manages cascade;
CREATE TABLE Manages(
    empname VARCHAR(50) NOT NULL,
    managername VARCHAR(50) NOT NULL
);
--
--
-- Insertions
--
--
--
--
INSERT INTO employee(empid, empname, street, city)
VALUES (1, 'Dipesh', 'abc', 'Trichy');
INSERT INTO employee(empid, empname, street, city)
VALUES (2, 'Apurva', 'xyz', 'Delhi');
INSERT INTO employee(empid, empname, street, city)
VALUES (3, 'Hari', 'pqr', 'Kathmanu');
INSERT INTO employee(empid, empname, street, city)
VALUES (4, 'Ram', 'mnop', 'Chennai');
INSERT INTO employee(empid, empname, street, city)
VALUES (5, 'Ishika', 'Thane', 'Mumbai');
INSERT INTO employee(empid, empname, street, city)
VALUES (6, 'Hedhav', 'Pune 1', 'Pune');
INSERT INTO works(empname, companyname, salary)
VALUES('Dipesh', 'State Bank Of India', 95000);
INSERT INTO works(empname, companyname, salary)
VALUES('Hedhav', 'State Bank Of India', 100000);
INSERT INTO works(empname, companyname, salary)
VALUES('Apurva', 'UCO Bank', 50500);
INSERT INTO works(empname, companyname, salary)
VALUES('Ram', 'Google', 5220);
INSERT INTO works(empname, companyname, salary)
VALUES('Ishika', 'Google', 5000);
INSERT INTO works(empname, companyname, salary)
VALUES('Hari', 'UCO Bank', 5400);
INSERT INTO company(companyname, city)
VALUES('Google', 'Chennai');
INSERT INTO company(companyname, city)
VALUES('UCO Bank', 'Bangalore');
INSERT INTO company(companyname, city)
VALUES('State Bank Of India', 'Hyderabad');
INSERT INTO manages(empname, managername)
VALUES('Dipesh', 'Mary');
INSERT INTO manages(empname, managername)
VALUES('Apurva', 'Joe');
INSERT INTO manages(empname, managername)
VALUES('Hari', 'Sita');
INSERT INTO manages(empname, managername)
VALUES('Ishika', 'Piyal');
INSERT INTO manages(empname, managername)
VALUES('Ram', 'Gita');
INSERT INTO manages(empname, managername)
VALUES('Hedhav', 'Shweta');
--
--
--
--
--
-- (i) Find the name of all employees who work for State Bank of India. 
select employee.empname
from employee,
    works
where employee.empname = works.empname
    and works.companyname = 'State Bank Of India';
-- (ii) Find the names and cities of residence of all employees who work for State Bank of India. 
select employee.empname,
    employee.city
from employee,
    works
where employee.empname = works.empname
    and works.companyname = 'State Bank Of India';
-- (iii) Create a view for employee based on salary in ascending order. 
create view myview as
select employee.empname,
    works.salary,
    works.companyname,
    employee.street,
    employee.city
from employee,
    works
where employee.empname = works.empname
order by salary asc;
select *
from myview;
-- (iv) Find all employees in the database who earn more than every employee of UCO Bank. 
select empname
from works
where salary > (
        select max(salary)
        from works
        where companyname = 'UCO Bank'
    );
-- (v) Find the employee in the database who earn minimum in state bank of India 
select empname
from works
where salary =(
        select min(salary)
        from works
        where companyname = 'State Bank Of India'
    );
-- (vi) Create a Function that displays the employee who earn maximum in SBI.
drop function if exists max_earner_sbi;
CREATE OR REPLACE FUNCTION max_earner_sbi() RETURNS Table(employee_name varchar(200)) LANGUAGE plpgsql as $$ begin return query
select empname as employee_name
from works
where salary = (
        select max(salary)
        from works
        where companyname = 'State Bank Of India'
    );
end;
$$;
select *
from max_earner_sbi();
-- (vii) Write a procedure which takes the city as input parameter and lists the names of all
-- employees belonging to that city.
Drop procedure if exists city_employee;
CREATE OR REPLACE PROCEDURE city_employee(
        city_name varchar(200),
        INOUT names varchar(200) default null
    ) LANGUAGE plpgsql AS $$ BEGIN
select empname into names
from employee
where city = city_name;
end;
$$;
Call city_employee('Trichy');
Call city_employee('Delhi');
-- (viii) Write a function that will display the number of employees with salary more than 50k.
drop function if exists fiftyk_plus_earners;
CREATE OR REPLACE FUNCTION fiftyk_plus_earners(out number_of_employees int) LANGUAGE plpgsql as $$ begin
SELECT count(*) into number_of_employees
FROM works
WHERE works.salary > 50000;
end;
$$;
select *
from fiftyk_plus_earners();
-- (ix) Write a procedure raise_sal which increases the salary of an employee. It accepts an
-- employee number and salary increase amount.
drop procedure if exists raise_sal;
CREATE PROCEDURE raise_sal(emp_no int, amount int) LANGUAGE plpgsql AS $$ begin
UPDATE works
SET salary = salary + amount
WHERE empname = (
        SELECT empname
        FROM employee
        WHERE empid = emp_no
    );
end;
$$;
-- Before
select *
from Works;
-- raise_sal for empid 1,which is Dipesh by 10k
CALL raise_sal(1, 10000);
-- After
select *
from Works;
-- (x)  Create a Procedure that displays the details of managers working in a bank
drop procedure if exists manager_details;
CREATE PROCEDURE manager_details(
    bank_name varchar(200),
    INOUT managers varchar(200) default null
) LANGUAGE plpgsql AS $$ begin
SELECT array_agg(managername) into managers
FROM employee,
    works,
    company,
    Manages
WHERE employee.empname = works.empname
    AND works.companyname = company.companyname
    AND employee.empname = Manages.empname
    AND company.companyname = bank_name;
end;
$$;
Call manager_details('UCO Bank');
Call manager_details('State Bank Of India');