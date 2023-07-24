SELECT m.id AS menu_id
FROM menu AS m
WHERE m.id NOT IN (
    SELECT menu_id
    FROM person_order
)
ORDER BY menu_id;