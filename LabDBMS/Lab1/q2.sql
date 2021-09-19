drop table if exists StudDep;

drop table if exists Students;

drop table if exists Department;

-- schema for tables
create table if not exists Students (
    Rollno int,
    Name varchar(50) not null,
    Marks int [ 6 ] not null,
    total int generated always as (
        Marks[1]+Marks[2]+Marks[3]+Marks[4]+Marks[5]+Marks[6]
    ) STORED,
    PRIMARY KEY (Rollno)
);

create table if not exists Department (
    Deptid int,
    Deptname varchar (255) not null,
    HODName varchar(50) not null,
    PRIMARY KEY (Deptid)
);

create table if not exists StudDep (
    Rollno int,
    Deptid int,
    FOREIGN KEY (Rollno) REFERENCES Students (Rollno),
    FOREIGN KEY (Deptid) REFERENCES Department(Deptid),
    PRIMARY KEY(Rollno, Deptid)
);

------------------------------------------------------------------------------
-- 2.1

-- 1) Insert 10 student details and 3 department details. Insert
-- details in the studdep table.
------------------------------------------------------------------------------
-- Student details
--i
insert into
    Students(Rollno, Name, Marks)
values
    (106119001, 'Dipesh', Array [ 80,75, 81,87, 77,72 ]);

--ii
insert into
    Students(Rollno, Name, Marks)
values
    (106119002,'Ram', Array [ 86, 75,81, 87,77,77 ]);

--iii
insert into
    Students(Rollno, Name, Marks)
values
    (106119003,'Sita',Array [ 80,75, 81,92,77,80 ]);

--iv
insert into
    Students(Rollno, Name, Marks)
values
    (106119004,'Laxman',Array [ 90,75, 71,87,77,70 ]);

--v
insert into
    Students(Rollno, Name, Marks)
values
    (106119005,'Bharat',Array [ 91,90,95,95,95,95 ]);

--vi
insert into
    Students(Rollno, Name, Marks)
values
    (107119001,'Arjun',Array [ 81,90,85,98,75,95 ]);

--vii
insert into
    Students(Rollno, Name, Marks)
values
    (107119002,'Bheem',Array [ 81, 70,95,70,85,85 ]);

--viii
insert into
    Students(Rollno, Name, Marks)
values
    (108119001,'Vishnu',Array [ 91,90,75,85,87,95 ]);

--ix
insert into
    Students(Rollno, Name, Marks)
values
    (108119002,'Shiva',Array [ 94,70,85,95,95,95 ]);

-- x
insert into
    Students(Rollno, Name, Marks)
values
    (108119003,'Laxmi',Array [ 84,70,88,75,85,85 ]);

-- 3 department details
insert into
    Department
values
    (1, 'CSE', 'Rajeswari  Sridhar');

insert into
    Department
values
    (2, 'ECE', 'Prof X');

insert into
    Department
values
    (3, 'EEE', 'Prof Y');

-- studdep details
insert into
    studdep
values
    (106119001, 1);

insert into
    studdep
values
    (106119002, 1);

insert into
    studdep
values
    (106119003, 1);

insert into
    studdep
values
    (106119004, 1);

insert into
    studdep
values
    (106119005, 1);

insert into
    studdep
values
    (107119001, 2);

insert into
    studdep
values
    (107119002, 2);

insert into
    studdep
values
    (108119001, 3);

insert into
    studdep
values
    (108119002, 3);

insert into
    studdep
values
    (108119003, 3);

------------------------------------------------------------------------------
------------------------------------------------------------------------------


------------------------------------------------------------------------------
-- 2.2

-- 2.Display the Student details if deptid is given
------------------------------------------------------------------------------

select * from Students inner join Studdep
on
    students.Rollno=studdep.Rollno 
where 
    studdep.deptid=1;
select * from Students inner join Studdep
on 
    students.Rollno=studdep.Rollno
where 
    studdep.deptid=2;

select * from Students inner join Studdep
on 
    students.Rollno=studdep.Rollno
where 
    studdep.deptid=3;
    

------------------------------------------------------------------------------
------------------------------------------------------------------------------


------------------------------------------------------------------------------
-- 2.3

-- 3.Display the department details if rollno is given
------------------------------------------------------------------------------

select * from Department inner join Studdep
on 
    Department.deptid=Studdep.deptid
where 
    Studdep.rollno = 106119001;

select * from Department inner join Studdep
on 
    Department.deptid=Studdep.deptid
where 
    Studdep.rollno = 107119001;

select * from Department inner join Studdep
on 
    Department.deptid=Studdep.deptid
where 
    Studdep.rollno = 108119001;
    

------------------------------------------------------------------------------
------------------------------------------------------------------------------


------------------------------------------------------------------------------
-- 2.4

-- 4.Display the student names who got total greater than 500
------------------------------------------------------------------------------

select Name , total from students where total > 500;


------------------------------------------------------------------------------
------------------------------------------------------------------------------


------------------------------------------------------------------------------
-- 2.5

-- 5.Display the HOD name of the CSE department
------------------------------------------------------------------------------

select HODName from Department where Deptname = 'CSE';


------------------------------------------------------------------------------
------------------------------------------------------------------------------


------------------------------------------------------------------------------
-- 2.6

-- 6.Display the student rollnos of the CSE department
------------------------------------------------------------------------------

select studdep.rollno, Department.deptname from Department inner join studdep
on
    studdep.deptid = Department.deptid
where
    Department.Deptname='CSE';
