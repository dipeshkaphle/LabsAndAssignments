-- drop tables if exists cascade
drop table if exists Patient cascade;
drop table if exists Test_Report cascade;
drop table if exists Hospital cascade;

-- CREATE a table named Patient with P_id, Patient_name, sex, age, area, city, H_id,
CREATE table Patient(
    P_id int primary key,
    Patient_name varchar(20),
    sex varchar(1),
    age int,
    area varchar(20),
    city varchar(20),
    H_id int
);

-- CREATE a table named Test_Report with T_id, P_id, H_id, reporting_date, test_result, discharge_date
CREATE table Test_Report(
    T_id int primary key,
    P_id int,
    H_id int,
    reporting_date date,
    test_result varchar(20),
    discharge_date date
);

-- CREATE a table named Hosptial with H_id, Hospital_Name, Location, State, T_id
CREATE table Hospital(
    H_id int primary key,
    Hospital_Name varchar(20),
    Location varchar(20),
    State varchar(20)
);

-- Alter table Hospital H_id is foriegn key to Hospital
alter table Patient add constraint FK_H_id foreign key(H_id) references Hospital(H_id);

-- Alter Table Test_Report P_id is foriegn key to Patient, H_id is foriegn key to Hospital
alter table Test_Report add constraint FK_P_id foreign key(P_id) references Patient(P_id);
alter table Test_Report add constraint FK_H_id foreign key(H_id) references Hospital(H_id);

-- Inserting Hospitals
insert into Hospital values(1, 'Apollo Hospital', 'City1', 'Maharashtra');
insert into Hospital values(2, 'Hospital2', 'City2', 'Maharashtra');
insert into Hospital values(3, 'Hospital3', 'Delhi', 'Tamil Nadu');
insert into Hospital values(4, 'Hospital4', 'City4', 'UP');
insert into Hospital values(5, 'Hospital5', 'City5', 'Karnataka');

-- Inserting Patients
insert into Patient values(1, 'Patient1', 'M', 13, 'Area1', 'City1', 1);
insert into Patient values(2, 'Patient2', 'F', 14, 'Area1', 'City1', 1);
insert into Patient values(3, 'Patient3', 'M', 17, 'Area2', 'City1', 2);
insert into Patient values(4, 'Patient4', 'F', 20, 'Area2', 'City1', 3);
insert into Patient values(5, 'Patient5', 'M', 25, 'Area2', 'City1', 3);
insert into Patient values(6, 'Patient6', 'F', 35, 'Area1', 'City2', 2);
insert into Patient values(7, 'Patient7', 'M', 47, 'Area2', 'City2', 4);
insert into Patient values(8, 'Patient8', 'F', 59, 'Area1', 'Delhi', 5);
insert into Patient values(9, 'Patient9', 'M', 65, 'Area2', 'Delhi', 1);
insert into Patient values(10, 'Patient10', 'F', 75, 'Area1', 'City4', 2);

-- Insert test_reports for the given patients AND hospitals
insert into Test_Report values(1, 1, 1, '2021-05-01', 'Positive', '2021-05-20');
insert into Test_Report values(2, 2, 1, '2021-05-02', 'Positive', '2021-05-25');
insert into Test_Report values(3, 3, 2, '2021-05-03', 'Negative', '2021-05-13');
insert into Test_Report values(4, 4, 3, '2021-05-04', 'Negative', '2021-05-10');
insert into Test_Report values(5, 5, 3, '2021-05-05', 'Negative', '2021-05-13');
insert into Test_Report values(6, 6, 2, '2021-07-06', 'Positive', '2021-08-03');
insert into Test_Report values(7, 7, 4, '2021-07-07', 'Positive', '2021-08-07');
insert into Test_Report values(8, 8, 5, '2021-07-08', 'Positive', '2021-07-28');
insert into Test_Report values(9, 9, 1, '2021-07-09', 'Positive', '2021-08-05');
insert into Test_Report values(10, 10, 2, '2021-07-10', 'Negative', '2021-08-09');

-------------------------------------------------------------------------------

-- 1.1 

-- Q1 Find the name of all patients who is lesser than 15 years old.

--------------------------------------------------------------------------------
SELECT Patient_name FROM Patient WHERE age < 15;



-------------------------------------------------------------------------------

-- 1.2

-- Q2 Find the nameof patients who has admitted in Apollohospital.

--------------------------------------------------------------------------------

SELECT Patient_name FROM Patient, Hospital 
    WHERE Patient.H_id = Hospital.H_id 
    AND Hospital_Name = 'Apollo Hospital';

-------------------------------------------------------------------------------

-- 1.3

-- Q3 Find the name of hospital that has a fastest recovery ratio.

--------------------------------------------------------------------------------

SELECT Hospital_Name, avg(discharge_date - reporting_date) 
    as days FROM Test_Report, Hospital 
    WHERE Test_Report.H_id = Hospital.H_id AND test_result = 'Negative' 
    GROUP BY Hospital_Name ORDER by days LIMIT 1;

-------------------------------------------------------------------------------

-- 1.4

-- Q4 Create a view on test results based on reporting date of last three months.

--------------------------------------------------------------------------------
DROP VIEW if exists last_three_months;

-- If we just want test_result , use this 
CREATE view last_three_months as
	SELECT test_result FROM Test_Report
		WHERE reporting_date > (NOW() - INTERVAL '3 MONTHS')::DATE;

-- For all details, use  this
--  CREATE view last_three_months as
	--  SELECT * FROM Test_Report
		--  WHERE reporting_date > (NOW() - INTERVAL '3 MONTHS')::DATE;
SELECT * FROM last_three_months;

    
-------------------------------------------------------------------------------

-- 1.5

-- Q5 Find name AND age of all patients whose test result is Negative 
-- FROM patient AND test_report.

--------------------------------------------------------------------------------
    
SELECT Patient_name, age FROM Patient, Test_Report 
    WHERE Patient.P_id = Test_Report.P_id 
    AND test_result = 'Negative';

    

-------------------------------------------------------------------------------

-- 1.6

-- Q6 Find the hotspot area in a district based on the test results.
--------------------------------------------------------------------------------
DROP view IF EXISTS hotspot_view;

CREATE view hotspot_view as SELECT area, city, count(*) as cases 
    FROM Patient, Test_Report 
        WHERE Patient.P_id = Test_Report.P_id 
        AND test_result = 'Positive' GROUP BY city, area;


SELECT DISTINCT temp.city, hotspot_view.area, temp.cases
FROM (SELECT city, max(cases) as cases FROM hotspot_view GROUP BY city) 
as temp,hotspot_view WHERE temp.cases = hotspot_view.cases 
    AND temp.city = hotspot_view.city;


-------------------------------------------------------------------------------

-- 1.7

-- Q7 List out the states, which has reported with maximum COVID 
--cases WHERE age is less than 18
--------------------------------------------------------------------------------
SELECT State, count(*) as case_count FROM Patient, Test_Report, Hospital 
    WHERE Patient.P_id = Test_Report.P_id 
    AND Test_Report.H_id = Hospital.H_id 
    AND age < 18 
    GROUP BY State 
    order by case_count desc LIMIT 1;


-------------------------------------------------------------------------------

-- 1.8

-- Q8 Find the name of the patients who belongs to same area in a particular city.
--------------------------------------------------------------------------------

SELECT area, array_agg(Patient_name) as people 
    FROM Patient 
    WHERE city = 'City1' GROUP BY area;

    
-------------------------------------------------------------------------------

-- 1.9

-- Q9 Find the number of female patient(s) who has admitted in her city itself
--------------------------------------------------------------------------------
    
SELECT count(*) FROM Patient, Hospital 
    WHERE Patient.H_id = Hospital.H_id 
    AND Patient.city = Hospital.location 
    AND Patient.sex='F';

    
    
-------------------------------------------------------------------------------

-- 1.10

-- Q10 find the name of hospital that has the highest number 
--of Positive patients in a particular state.
--------------------------------------------------------------------------------
SELECT Hospital_Name, count(*) as patient_count
    FROM Patient, Test_Report, Hospital
        WHERE Patient.P_id = Test_Report.P_id
        AND Test_Report.H_id = Hospital.H_id
        AND State = 'Maharashtra'
        AND test_result = 'Positive'
        GROUP BY Hospital.H_id
        order by patient_count desc LIMIT 1;
