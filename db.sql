-- combined for lecturer and candidate
-- type: 0 is lecturer, 1 is candidate, others are invalid
create table User (
	username TEXT KEY NOT NULL,
	password TEXT NOT NULL,
	name TEXT NOT NULL,
	type INT NOT NULL,
	testAccId TEXT
);

create table Topic (
	topicId INTEGER PRIMARY KEY,
	totalMarks INTEGER NOT NULL
);

create table Question (
	questionId INTEGER PRIMARY KEY,
	topicId INTEGER NOT NULL,
	marks INTEGER NOT NULL,
	question TEXT NOT NULL,
	answer TEXT NOT NULL,
	FOREIGN KEY(topicId) REFERENCES Topic(topicId)
);

create table QuestionOption (
	questionId INTEGER NOT NULL,
	answer TEXT NOT NULL,
	FOREIGN KEY(questionId) REFERENCES Question(questionId)
);

create table Attempt (
	topicId INTEGER NOT NULL,
	testAccId TEXT NOT NULL,
	totalMarks INTEGER NOT NULL,
	FOREIGN KEY(topicId) REFERENCES Topic(topicId),
	FOREIGN KEY(testAccId) REFERENCES User(testAccId)
);

insert into User values('lect', 'zyx', 'lecturer', 0, NULL);