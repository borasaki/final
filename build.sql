drop table if exists response;
drop table if exists question;
drop table if exists user;

CREATE TABLE question (
    id INT NOT NULL,
    question VARCHAR(50) NOT NULL,
    PRIMARY KEY (id)
) ENGINE = innodb;

CREATE TABLE response (
    qid INT NOT NULL,
    answer INT NOT NULL,
    foreign key (qid) references question(id)
) ENGINE = innodb;

INSERT INTO question VALUES
(1,"Did you like this course?"),
(2,"Do you understand this project?"),
(3,"Do you like the INFO Capstone course?");


SELECT q.question as 'Query', r.answer as 'Answer', count(r.answer) as 'Num Answer'
    from question as q
    join response as r on r.qid = q.id
group by q.id, r.answer
order by q.id;