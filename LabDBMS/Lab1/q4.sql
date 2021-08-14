drop table if exists sales;
drop table if exists options ;
drop table if exists salesperson;
drop table if exists car;

-----------------------------------------------------------------

-- car(serial_no, model, manufacturer, price)
-- serial_no – Primary key

-- options(serial_no, option_name, price)
-- serial_no – Foreign key

-- sales(salesperson_id, serial_no, date, sale_price)
-- serial_no – Foreign key
-- salesperson_id – Foreign key

-- salesperson(salesperson_id, name, phone)
-- salesperson_id – Primary key

-----------------------------------------------------------------
create table car(
    serial_no int,
    model varchar(255),
    manufacturer varchar(255),
    price float,
    primary key(serial_no)
);

create table options(
    serial_no int,
    option_name varchar(255),
    price float,
    foreign key(serial_no) REFERENCES car(serial_no)
);

create table salesperson(
    salesperson_id int,
    name varchar(50),
    phone varchar(10),
    primary key (salesperson_id)
);

create table sales(
    salesperson_id int,
    serial_no int,
    date DATE,
    sale_price float,
    foreign key(salesperson_id) REFERENCES salesperson(salesperson_id),
    foreign key(serial_no) REFERENCES car(serial_no)
);


--------------------------------------------------------------------
-- dummy data
-------------------------------------------------------------------

insert into car values(1,'Nano','Tata',150000);
insert into car values(2,'Model S','Tesla',6000000);

insert into options values(2,'Matte black coloring',6100000);
insert into options values(2,'Red coloring',6050000);

insert into salesperson values(1,'John','0123456789');
insert into salesperson values(2,'Dipesh','9876543210');

insert into sales values(2,1,CURRENT_DATE, 170000 );
insert into sales values(2,2,CURRENT_DATE, 6200000);
insert into sales values(1,1,CURRENT_DATE, 180000);
insert into sales values(1,1,CURRENT_DATE, 160000);


--------------------------------------------------------------------
-- 4.1

-- 1.For the sales person named ‘John’ list the following information for all
-- the cars sold : serial no, manufacturer, sale_price
-------------------------------------------------------------------
select temp2.serial_no, car.manufacturer, temp2.sale_price  from 
    (select sales.serial_no,sales.sale_price from (select salesperson_id from salesperson 
        where 
        name='John') as temp inner join sales
        on temp.salesperson_id = sales.salesperson_id) as temp2 inner join car
        on temp2.serial_no = car.serial_no;



--------------------------------------------------------------------
-- 4.2

-- 2.List the serial_no and model of cars that have no options
-------------------------------------------------------------------
select temp.serial_no,car.model from (select serial_no from car
    EXCEPT
    select serial_no from options) as temp inner join car
    on car.serial_no = temp.serial_no;

--------------------------------------------------------------------
-- 4.3

-- 3.List the serial_no, model, sale_price 
-- for the cars that have optional parts.
-------------------------------------------------------------------

select temp.serial_no,car.model,car.price from (select serial_no from car
    INTERSECT
    select serial_no from options) as temp inner join car
    on car.serial_no = temp.serial_no;

--------------------------------------------------------------------
-- 4.4

-- 4.Modify the phone no of a particular sales person
-------------------------------------------------------------------

-- Before
select * from salesperson where name = 'Dipesh';

-- Update
update salesperson
set phone = '1235647890'
where name = 'Dipesh';

-- After
select * from salesperson where name = 'Dipesh';