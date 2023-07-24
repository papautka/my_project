start transaction; --Session1

update pizzeria set rating = '5' --Session1
where name = 'Pizza Hut'; --Session1

select * from pizzeria --Session1
where name = 'Pizza Hut'; --Session1

select * from pizzeria --Session2
where name = 'Pizza Hut'; --Session2

commit; --Session1

select * from pizzeria  --Session2
where name = 'Pizza Hut'; --Session2
