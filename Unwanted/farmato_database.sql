CREATE TABLE user_login (
  user_unique_id varchar(100) PRIMARY KEY,
  user_full_name char(50) NOT NULL,
  user_phone_no int(20) NOT NULL,
  user_password varchar(255) NOT NULL,
  user_email_id varchar(100) NOT NULL
)


CREATE TABLE cookie_data (
    cookie_user_unique_id varchar(100) NOT NULL,
    token_id_1 varchar(50) NOT NULL,
    token_id_2 varchar(50) NOT NULL,
    FOREIGN KEY (cookie_user_unique_id) REFERENCES user_login(user_unique_id)
)


CREATE TABLE user_nodemcu_com (
  unc_user_unique_id varchar(100) NOT NULL,
  pump_status BOOLEAN,
  tank_water_level int,
  sump_water_level int,
  -- user_freeze_flag BOOLEAN,
  -- nodemcu_freeze_flag BOOLEAN,
  user_intervention_flag BOOLEAN,
  FOREIGN KEY (unc_user_unique_id) REFERENCES user_login(user_unique_id)
)

INSERT INTO user_nodemcu_com  VALUES ('0e7f970107b5e113284bbb706da47ba2', 0, 0, 0, 0, 0, 0, 0, 0);


