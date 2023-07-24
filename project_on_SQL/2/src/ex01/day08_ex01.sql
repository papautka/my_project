SHOW TRANSACTION ISOLATION LEVEL; --Session1
SHOW TRANSACTION ISOLATION LEVEL; --Session2

begin; --Session1
begin; --Session2

select * from pizzeria where name = 'Pizza Hut'; --Session1
select * from pizzeria where name = 'Pizza Hut'; --Session2

update pizzeria set rating = '4'  --Session1
where name = 'Pizza Hut';         --Session2

update pizzeria set rating = '3.6' --Session1
where name = 'Pizza Hut';          --Session2

commit; --Session1
commit; --Session2

select * from pizzeria where name = 'Pizza Hut'; --Session1
select * from pizzeria where name = 'Pizza Hut'; --Session2