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
    sale_price float,
    foreign key(salesperson_id) REFERENCES salesperson(salesperson_id),
    foreign key(serial_no) REFERENCES car(serial_no)
);