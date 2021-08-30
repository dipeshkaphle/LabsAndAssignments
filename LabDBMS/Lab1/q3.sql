drop table if exists salerep_expense;
drop table if exists trip;
drop table if exists salesperson;
--------------------------------------------------------
-- salesperson(ssn, name, start_year, dept_no)
-- ssn – Primary Key

-- trip(ssn, from_city, to_city, departure_date, return_date, trip_id))
-- ssn – Foreign key
-- trip_id – Primary key

-- salerep_expense(trip_id, expense_type,amount)
-- trip_id – Foreign key
--------------------------------------------------------

create table if not exists salesperson(
    ssn int,
    name varchar(50),
    start_year int,
    dept_no int,
    Primary key(ssn)
); 

create table if not exists trip(
    ssn int ,
    from_city varchar(100),
    to_city varchar(100),
    departure_date DATE,
    return_date DATE,
    trip_id int primary key,
    Foreign key(ssn) REFERENCES salesperson(ssn)
);

-- The expense types are ‘TRAVEL’, ‘STAY’ and ‘FOOD’ 
create type exp_type as ENUM ('TRAVEL','STAY','FOOD');
create table if not exists salerep_expense(
    trip_id int ,
    expense_type exp_type,
    amount float,
    foreign key(trip_id) REFERENCES trip(trip_id),
    primary key(trip_id,expense_type)
);

---------------------------------------------------------------
-- Inserting dummy data
---------------------------------------------------------------
-- Filling salesperson db
insert into salesperson values(1,'Dipesh',2020,1);
insert into salesperson values(2,'Ram',2021,2);
insert into salesperson values(1000,'Shyam',2019,3);

-- Filling trip db
insert into trip values(1,'Kathmandu','Trichy','2019-07-22','2019-07-30',1);
insert into trip values(2,'Trichy','Chennai','2019-12-30','2020-12-31',2);
insert into trip values(2,'Trichy','Chennai','2019-12-30','2020-12-31',4);
insert into trip values(1000,'Pune','Chennai','2020-12-30','2021-01-02',3);

-- Filling salerep_expense db
insert into salerep_expense values(1,'TRAVEL',5000);
insert into salerep_expense values(1,'STAY',1000);
insert into salerep_expense values(1,'FOOD',300);
insert into salerep_expense values(2,'TRAVEL',1200);
insert into salerep_expense values(2,'FOOD',300);
insert into salerep_expense values(3,'TRAVEL',800);
insert into salerep_expense values(3,'FOOD',300);
insert into salerep_expense values(3,'STAY',1000);
insert into salerep_expense values(4,'TRAVEL',1200);
insert into salerep_expense values(4,'FOOD',300);



--------------------------------------------------------------
--3.1

-- 1. Give the details (all attributes of trip relation) for trips that
-- exceed Rs2000.
--------------------------------------------------------------
-- select * from (
--     select trip.* , sum(salerep_expense.amount) as cost 
--     from trip inner join salerep_expense
--     on
--         trip.trip_id = salerep_expense.trip_id
--     group by trip.trip_id) as temp 
-- where temp.cost > 2000;


select trip.* , sum(salerep_expense.amount) as cost 
    from trip inner join salerep_expense
    on
        trip.trip_id = salerep_expense.trip_id
    group by trip.trip_id
    having sum(salerep_expense.amount) > 2000;
    


--------------------------------------------------------------
-- 3.2

-- 2.Print the ssn of salesperson who took trips to chennai more than once
--------------------------------------------------------------
-- select temp2.ssn from
--     (select temp.ssn , count(temp.ssn) as to_chennai_trip_cnt
--     from (
--         select trip.ssn from trip  where trip.to_city = 'Chennai'
--         ) as temp
--     group by temp.ssn) as temp2
-- where temp2.to_chennai_trip_cnt > 1;

select temp.ssn from (
    select trip.ssn from trip where trip.to_city='Chennai'
) as temp group by temp.ssn having count(temp.ssn) > 1;


--------------------------------------------------------------
-- 3.3

-- 3.Print the total trip expenses incurred by 
-- the salesperson with ssn = 1000
--------------------------------------------------------------
select sum(tmp2.amount) from (select * from (
    select trip_id from trip 
    where trip.ssn = 1000) as tmp inner join salerep_expense
    on tmp.trip_id = salerep_expense.trip_id) as tmp2;

--------------------------------------------------------------
-- 3.4

-- 4.Display the salesperson details in the sorted order 
-- based on name.
--------------------------------------------------------------
select * from salesperson order by name ;

