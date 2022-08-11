Drop table if exists Student;
CREATE Table IF NOT EXISTS Student (
    rollno int NOT NULL AUTO_INCREMENT PRIMARY KEY,
    username VARCHAR(255) NOT NULL,
    password varchar(255) NOT NULL,
    score int  
);
INSERT INTO Student (rollno, username, password)
VALUES (1, "A","pass"),
    (2, "B","pass"),
    (3, "C","pass"),
    (4, "D","pass"),
    (5, "E","pass"),
    (6, "F","pass"),
    (7, "G","pass"),
    (8, "H","pass"),
    (9, "I","pass"),
    (10, "J","pass"),
    (11, "K","pass"),
    (12, "L","pass"),
    (13, "M","pass"),
    (14, "M","pass"),
    (15, "N","pass"),
    (29, "Dipesh","pass");
-- Question Table
drop TABLE if exists Question;
CREATE Table IF NOT EXISTS Question (
    qno int(11) NOT NULL AUTO_INCREMENT,
    question VARCHAR(255) NOT NULL,
    option1 VARCHAR(255) NOT NULL,
    option2 VARCHAR(255) NOT NULL,
    option3 VARCHAR(255) NOT NULL,
    option4 VARCHAR(255) NOT NULL,
    answer VARCHAR(255) NOT NULL,
    PRIMARY KEY (qno)
);
INSERT INTO Question (
        question,
        option1,
        option2,
        option3,
        option4,
        answer
    )
VALUES (
        "1+2",
        "1",
        "2",
        "3",
        "4",
        "3"
    ),
    (
        "2*3",
        "2",
        "4",
        "6",
        "8",
        "6"
    ),
    (
        "3*5",
        "6",
        "10",
        "15",
        "20",
        "15"
    ),
    (
        "100/20",
        "1",
        "3",
        "5",
        "7",
        "5"
    ),
    (
        "100/4",
        "10",
        "20",
        "25",
        "30",
        "25"
    );
