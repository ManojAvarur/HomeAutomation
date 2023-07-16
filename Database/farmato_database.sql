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
  time_stamp datetime not null,
  unc_node_mcu_unique_id varchar(100) PRIMARY KEY,

  sump_status int NOT NULL,
  sump_low_limit int NOT NULL,
  sump_high_limit int NOT NULL,

  tank_status int NOT NULL,
  tank_low_limit int NOT NULL,
  tank_high_limit int NOT NULL,

  motor_status boolean NOT NULL,
  debug_log varchar(200),
  is_controlled_locally boolean NOT NULL,
  pump_manual_overide_data_flag tinyint,
  FOREIGN KEY (unc_node_mcu_unique_id) REFERENCES registered_node_mcu(node_mcu_unique_id)
);

CREATE TABLE user_requests (
  time_stamp datetime,
  unc_node_mcu_unique_id varchar(100) PRIMARY KEY,
  pump_manual_overide_request BOOLEAN,
  pump_on_off_status BOOLEAN,
  pump_take_over_complete_control boolean,
  node_mcu_is_controled_by_user_id varchar(100) UNIQUE,
  phpsessid varchar(50) UNIQUE,
  FOREIGN KEY (node_mcu_is_controled_by_user_id) REFERENCES user_login(user_unique_id),
  FOREIGN KEY (unc_node_mcu_unique_id) REFERENCES registered_node_mcu(node_mcu_unique_id)
);

CREATE TABLE app_version ( 
  time_stamp DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP , 
  app_current_version FLOAT(10) NOT NULL , 
  download_link VARCHAR(100) NOT NULL , 
  next_app_version_available BOOLEAN NOT NULL DEFAULT '0'
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

-- ALTER TABLE node_mcu_data
--     CHANGE time_stamp 
--         time_stamp TIMESTAMP NOT NULL
--                     DEFAULT CURRENT_TIMESTAMP
--                     ON UPDATE CURRENT_TIMESTAMP;



INSERT INTO node_mcu_data ( unc_node_mcu_unique_id, sump_status, tank_status, motor_status, debug_log  ) 
VALUES ( "4bb7abf6d3782611339eb6fe6326b96b6b4fca3d6f7e16f33367268806c5512c", -1, -1, -1, "Nothing to display" );

