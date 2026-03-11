CREATE TABLE IF NOT EXISTS users (
    user_id INTEGER PRIMARY KEY,
    username VARCHAR(31) UNIQUE NOT NULL,
    password VARCHAR(51) NOT NULL,
    balance FLOAT NOT NULL DEFAULT 0.0
);
CREATE TABLE IF NOT EXISTS transfers (
    transfer_id INTEGER PRIMARY KEY,
    from_user INTEGER,
    to_user INTEGER,
    amount INTEGER NOT NULL,
    FOREIGN KEY(from_user) REFERENCES users(user_id),
    FOREIGN KEY(to_user) REFERENCES users(user_id)
);