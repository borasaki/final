drop table if exists response;
drop table if exists question;
drop table if exists user;

CREATE TABLE question (
    id INT NOT NULL,
    question VARCHAR(50) NOT NULL,
    PRIMARY KEY (id)
) ENGINE = innodb;

CREATE TABLE response (
    id INT auto_increment NOT NULL,
    qid INT NOT NULL,
    answer INT NOT NULL,
    PRIMARY KEY (id),
    foreign key (qid) references question(id)
) ENGINE = innodb;

INSERT INTO question VALUES
(1,"Did you like this course?"),
(2,"Do you understand this project?"),
(3,"Do you like the INFO Capstone course?");