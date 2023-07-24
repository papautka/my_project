BEGIN TRANSACTION ISOLATION LEVEL READ COMMITTED; --Session1
BEGIN TRANSACTION ISOLATION LEVEL READ COMMITTED; --Session2

select sum(rating) from pizzeria; --Session1

update pizzeria set rating = '1'  --Session2
where name like 'Pizza Hut';      --Session2
commit;                           --Session2

select sum(rating) from pizzeria;   --Session1
commit;                             --Session1
select sum(rating) from pizzeria;   --Session1

select sum(rating) from pizzeria;   --Session2