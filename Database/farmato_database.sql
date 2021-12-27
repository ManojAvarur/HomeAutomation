-- Check out json data type in mysql

CREATE TABLE registered_node_mcu (
  node_mcu_unique_id varchar(100) PRIMARY KEY
);

CREATE TABLE user_login (
  user_unique_id varchar(100) PRIMARY KEY,
  user_node_mcu_reference VARCHAR(100) NOT NULL,
  user_full_name char(50) NOT NULL,
  user_password varchar(255) NOT NULL,
  user_email_id varchar(100) NOT NULL,
  user_is_admin boolean NOT NULL,
  FOREIGN KEY (user_node_mcu_reference) REFERENCES registered_node_mcu(node_mcu_unique_id)
);

CREATE TABLE cookie_data (
    cookie_user_unique_id varchar(100) NOT NULL,
    token_id_1 varchar(50) NOT NULL,
    token_id_2 varchar(50) NOT NULL,
    FOREIGN KEY (cookie_user_unique_id) REFERENCES user_login(user_unique_id)
);

CREATE TABLE node_mcu_data (
  time_stamp datetime DEFAULT current_timestamp(),
  unc_node_mcu_unique_id varchar(100) NOT NULL,
  sump_status tinyint NOT NULL,
  tank_status tinyint NOT NULL,
  motor_status boolean NOT NULL,
  debug_log varchar(200),
  FOREIGN KEY (unc_node_mcu_unique_id) REFERENCES registered_node_mcu(node_mcu_unique_id)
);

CREATE TABLE user_requests (
  time_stamp datetime,
  unc_node_mcu_unique_id varchar(100) NOT NULL,
  pump_manual_overide_request BOOLEAN,
  pump_on_off_status BOOLEAN,
  pump_take_over_complete_control boolean,
  node_mcu_is_controled_by_user_id varchar(100),
  FOREIGN KEY (node_mcu_is_controled_by_user_id) REFERENCES user_login(user_unique_id),
  FOREIGN KEY (unc_node_mcu_unique_id) REFERENCES registered_node_mcu(node_mcu_unique_id)
);

-- CREATE TABLE user_nodemcu_com (
--   time_stamp datetime DEFAULT current_timestamp(),
--   unc_node_mcu_unique_id varchar(100) NOT NULL,

--   sump_status tinyint NOT NULL,
--   tank_status tinyint NOT NULL,
--   motor_status boolean NOT NULL,

--   debug_log varchar(200),

--   pump_manual_overide_request BOOLEAN,
--   pump_on_off_status BOOLEAN,
--   pump_take_over_complete_control boolean,

--   node_mcu_is_controled_by_user_id varchar(100),
--   FOREIGN KEY (node_mcu_is_controled_by_user_id) REFERENCES user_login(user_unique_id),
--   FOREIGN KEY (unc_node_mcu_unique_id) REFERENCES registered_node_mcu(node_mcu_unique_id)
-- );

-- ALTER TABLE user_nodemcu_com
--     CHANGE time_stamp 
--         time_stamp TIMESTAMP NOT NULL
--                     DEFAULT CURRENT_TIMESTAMP
--                     ON UPDATE CURRENT_TIMESTAMP;

-- ALTER TABLE user_requests
--     CHANGE time_stamp 
--         time_stamp TIMESTAMP NOT NULL
--                     DEFAULT CURRENT_TIMESTAMP
--                     ON UPDATE CURRENT_TIMESTAMP;

ALTER TABLE node_mcu_data
    CHANGE time_stamp 
        time_stamp TIMESTAMP NOT NULL
                    DEFAULT CURRENT_TIMESTAMP
                    ON UPDATE CURRENT_TIMESTAMP;



INSERT INTO node_mcu_data ( unc_node_mcu_unique_id, sump_status, tank_status, motor_status, debug_log  ) 
VALUES ( "6b86b273ff34fce19d6b804eff5a3f5747ada4eaa22f1d49c01e52ddb7875b4b", -1, -1, -1, "Nothing to display" );
