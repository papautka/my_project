BEGIN TRANSACTION ISOLATION LEVEL REPEATABLE READ;  --Session1
BEGIN TRANSACTION ISOLATION LEVEL REPEATABLE READ;  --Session2

select sum(rating) from pizzeria;   --Session1

update pizzeria set rating = '5'    --Session2
where name like 'Pizza Hut';        --Session2
commit;                             --Session2

select sum(rating) from pizzeria;   --Session1
commit;                             --Session1
select sum(rating) from pizzeria;   --Session1

select sum(rating) from pizzeria;   --Session2