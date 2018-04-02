// Given the mid, show the member if he/she is registered in a class
select m.name,m.mid, w.name from members m, workoutclasses w where m.mid = w.mid and m.mid =  :1;


// Show the members with expired membership
select name,mid,expireDate from members where sysdate > expireDate

// Given a Trainer level, show the name
select name from trainers where Tlevel = :1


// Add a member
insert into Members values(:1,:2,:3,sysdate,to_date(:4,'yyyy/mm/dd'))

// Update membership
update members set expireDate = to_date(:1,'yyyy/mm/dd') where members.mid = :2

// Check for availabe rooms
select rno from rooms where tid is null
