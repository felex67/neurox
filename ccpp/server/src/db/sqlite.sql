-- Активные игры
CREATE TABLE game_active (
    id INTEGER PRIMARY KEY,
    x_id INTEGER NOT NULL,
    o_id INTEGER NOT NULL,
    dump BLOB СРУСЛ (length(dump) = 24) NOT NULL,
    create_time DATETIME NOT NULL,
    start_time DATETIME NOT NULL,
    end_time DATETIME,      -- DEFAULT NULL не нужно указывать, NULL разрешен по умолчанию
    turn INTEGER NOT NULL,
    winner INTEGER DEFAULT 0
);
