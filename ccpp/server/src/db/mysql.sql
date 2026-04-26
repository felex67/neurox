-- Активные игры

CREATE TABLE game_active (
    id INT PRIMARY KEY,
    x_id INT NOT NULL,
    o_id INT NOT NULL,
    dump BINARY(24) NOT NULL,  -- фиксированная длина 24 байта
    create_time TIMESTAMP(3) NOT NULL,
    start_time TIMESTAMP(3) NOT NULL,
    end_time TIMESTAMP(3),
    turn INT NOT NULL,
    winner INT DEFAULT 0
);