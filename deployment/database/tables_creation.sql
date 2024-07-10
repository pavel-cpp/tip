--     "Text Insertion Program (TIP)" is a software
--     for client management and generating unique images for each client.
--     Copyright (C) 2024  Pavel Remdenok
--
--     This program is free software: you can redistribute it and/or modify
--     it under the terms of the GNU General Public License as published by
--     the Free Software Foundation, either version 3 of the License, or
--     (at your option) any later version.
--
--     This program is distributed in the hope that it will be useful,
--     but WITHOUT ANY WARRANTY; without even the implied warranty of
--     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
--     GNU General Public License for more details.
--
--     You should have received a copy of the GNU General Public License
--     along with this program.  If not, see <https://www.gnu.org/licenses/>.

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
    base64    bytea,
    id     serial
        constraint image_pk
            primary key
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

