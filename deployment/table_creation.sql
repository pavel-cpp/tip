create table if not exists main.font_settings
(
    id         serial
        constraint settings_pkey
            primary key,
    font       varchar(255),
    color      varchar(7),
    position_x integer,
    position_y integer,
    size       integer,
    bold       boolean
);

create table if not exists main.image
(
    url    text,
    id     serial
        constraint image_pk
            primary key,
    format text
);

create table if not exists main.advanced_settings_passwords
(
    password text
);

create table if not exists main.clients
(
    id           serial
        primary key,
    name         varchar(255),
    phone_number varchar(255),
    status       boolean default false
);

