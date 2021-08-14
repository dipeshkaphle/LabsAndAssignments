-- can skip
-- I'm only doing this so that the output remains the same 
-- even after multiple runs
DROP table if exists Workson ;
DROP table if exists Employee ;
DROP table if exists Project ;

---------------------------------------
---------------------------------------
-- creating tables

create table if not exists Employee(
	Empid int,
	Empname varchar(50),
	Address varchar(255),
	Doj Date,
	Salary float,
	PRIMARY KEY(Empid)
);

create table if not exists Project(
	Projectno int,
	Duration int,
	Projectname varchar(255),
	PRIMARY KEY(Projectno)
);


create table if not exists Workson(
	Empid int,
	Projno int,
	FOREIGN KEY(Empid)
		REFERENCES Employee(Empid),
	FOREIGN KEY(Projno)
		REFERENCES Project(Projectno),
	PRIMARY KEY(Empid,Projno)
);

---------------------------------------
---------------------------------------

-- populating tables

-- Employee table
insert into Employee values (1,'Dipesh Kafle', 'Nepal',CURRENT_DATE, 1000);
insert into Employee values (2,'Ram ', 'India',CURRENT_DATE, 2000);
insert into Employee values (3,'Sita', 'Nepal',CURRENT_DATE, 1500);
insert into Employee values (4,'Bharat', 'India',CURRENT_DATE, 500);

--  Project table
insert into Project values(1,10,'Find a job');
insert into Project values(2,1,'Marry Sita');
insert into Project values(3,1,'Marry Ram');

-- Workson table
insert into Workson values(1,1);
insert into Workson values(2,2);
insert into Workson values(3,3);
insert into Workson values(4,1);



--------------------------------------------------
--------------------------------------------------
-- Part 1
select * from Employee order by Empname DESC;
--------------------------------------------------
--------------------------------------------------



--------------------------------------------------
--------------------------------------------------
-- Part2 


-- valid
select * from Project where Projectno = 1;
-- valid
select * from Project where Projectno = 2;
-- valid
select * from Project where Projectno = 3;
-- not valid, will give empty
select * from Project where Projectno = 4;

--------------------------------------------------
--------------------------------------------------


--------------------------------------------------
--------------------------------------------------

-- Part 3

select Empname from Employee where Empname like 'B%';

--------------------------------------------------
--------------------------------------------------



--------------------------------------------------
--------------------------------------------------

-- Part 4
select Empid from Workson where Projno=1;
select Empid from Workson where Projno=2;
select Empid from Workson where Projno=3;