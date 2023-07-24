BEGIN TRANSACTION ISOLATION LEVEL REPEATABLE READ; --Session1
BEGIN TRANSACTION ISOLATION LEVEL REPEATABLE READ; --Session2

select * from pizzeria where name like 'Pizza Hut'; --Session1
select * from pizzeria where name like 'Pizza Hut'; --Session2

update pizzeria set rating = '4'  --Session1
where name like 'Pizza Hut';      --Session1


update pizzeria set rating = '3.6'  --Session2
where name = 'Pizza Hut';           --Session2

 commit; --Session1
 commit; --Session2


select * from pizzeria where name like 'Pizza Hut'; --Session1
select * from pizzeria where name like 'Pizza Hut'; --Session2