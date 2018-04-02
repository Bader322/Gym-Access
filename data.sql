--
--Members--							MID			NAME					PHONE#				JOIN DATE										EXPIRAY DATE
insert into Members values('1234567890','Bader Alsaleh','2507972507',to_date('2017/01/01','yyyy/mm/dd'),to_date('2017/04/04','yyyy/mm/dd'));
insert into Members values('1234567891','BatMan','2507971010',to_date('2017/03/01','yyyy/mm/dd'),to_date('2018/04/04','yyyy/mm/dd'));
insert into Members values('1234567892','Motaz','2507972020',to_date('2017/02/01','yyyy/mm/dd'),to_date('2017/04/12','yyyy/mm/dd'));
insert into Members values('1234567893','Huizhu Liu','2507974040',to_date('2017/06/01','yyyy/mm/dd'),to_date('2017/09/09','yyyy/mm/dd'));
insert into Members values('1234567894','John Legened','2507975050',to_date('2017/03/01','yyyy/mm/dd'),to_date('2019/04/04','yyyy/mm/dd'));
insert into Members values('1234567895','Luigi','2507976060',to_date('2017/06/01','yyyy/mm/dd'),to_date('2019/02/04','yyyy/mm/dd'));
insert into Members values('1234567896','Peter Walsh','2507977070',to_date('2017/03/01','yyyy/mm/dd'),to_date('2017/05/12','yyyy/mm/dd'));
insert into Members values('1234567897','Super Mario','2507978080',to_date('2017/07/01','yyyy/mm/dd'),to_date('2017/07/02','yyyy/mm/dd'));
insert into Members values('1234567898','Basheema Basheema','2507979090',to_date('2017/08/01','yyyy/mm/dd'),to_date('2017/12/12','yyyy/mm/dd'));
insert into Members values('1234567899','Rick','2507970000',to_date('2017/02/01','yyyy/mm/dd'),to_date('2018/01/20','yyyy/mm/dd'));
insert into Members values('1234567812','Alex King','2507972222',to_date('2017/02/01','yyyy/mm/dd'),to_date('2017/04/01','yyyy/mm/dd'));

----Trainers -----				#TID		NAME		Trainer Level
insert into Trainers values('12345','Jackie Chan','5');
insert into Trainers values('11111','Jackie Nick','2');
insert into Trainers values('22222','Ki Logan','4');
insert into Trainers values('44444','Nicolas Cage','4');
insert into Trainers values('55555','Mohammd Ali','3');

insert into Trainers values('66666','Mike Tyson','5');
insert into Trainers values('77777','Jack Nick','2');
insert into Trainers values('88888','Super MAN','5');



	------ Rooms --------   rno	 tid
insert into Rooms values ('115','12345');
insert into Rooms values ('105','11111');
insert into Rooms values ('106','22222');
insert into Rooms values ('107','55555');
insert into rooms values ('108','');


-- --- WorkOut Classes --- ----	--wcid	     name  -- rno,  	tid      mid
insert into WorkoutClasses values('33331','Spinning','115','12345','1234567890');
insert into WorkoutClasses values('33339','Yoga','105','12345','1234567891');
insert into WorkoutClasses values('33332','Boot Camp','106','11111','1234567892');
insert into WorkoutClasses values('33333','Boxing','107','22222','1234567893');
