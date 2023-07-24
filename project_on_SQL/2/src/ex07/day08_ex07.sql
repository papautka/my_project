BEGIN TRANSACTION ISOLATION LEVEL REPEATABLE READ; 	--Session1
BEGIN TRANSACTION ISOLATION LEVEL REPEATABLE READ;	--Session2

update pizzeria set rating = '4.99' where id = '1'; --Session1

update pizzeria set rating = '4.88' where id = '2';	--Session2

update pizzeria set rating = '4.77' where id = '2'; --Session1

update pizzeria set rating = '4.66' where id = '1'; --Session2

commit;	--Session1

commit;	--Session2