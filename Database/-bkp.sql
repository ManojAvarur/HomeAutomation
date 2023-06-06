-- phpMyAdmin SQL Dump
-- version 5.2.0
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Generation Time: Jun 06, 2023 at 02:47 PM
-- Server version: 10.4.24-MariaDB
-- PHP Version: 8.1.6

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `homeautomation`
--

-- --------------------------------------------------------

--
-- Table structure for table `app_version`
--

CREATE TABLE `app_version` (
  `time_stamp` datetime NOT NULL DEFAULT current_timestamp(),
  `app_current_version` float NOT NULL,
  `download_link` varchar(100) NOT NULL,
  `next_app_version_available` tinyint(1) NOT NULL DEFAULT 0
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- --------------------------------------------------------

--
-- Table structure for table `cookie_data`
--

CREATE TABLE `cookie_data` (
  `cookie_user_unique_id` varchar(100) NOT NULL,
  `token_id_1` varchar(50) NOT NULL,
  `token_id_2` varchar(50) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `cookie_data`
--

INSERT INTO `cookie_data` (`cookie_user_unique_id`, `token_id_1`, `token_id_2`) VALUES
('32a4b36497b941f4e0c478e952129baa', '37a786b9bb48be035335e714d00f4d49', '7bf8c56f7f90921dc1a4e0383f90f77c');

-- --------------------------------------------------------

--
-- Table structure for table `node_mcu_data`
--

CREATE TABLE `node_mcu_data` (
  `time_stamp` datetime NOT NULL,
  `unc_node_mcu_unique_id` varchar(100) NOT NULL,
  `sump_status` tinyint(4) NOT NULL,
  `tank_status` tinyint(4) NOT NULL,
  `motor_status` tinyint(1) NOT NULL,
  `debug_log` varchar(200) DEFAULT NULL,
  `is_controlled_locally` tinyint(1) NOT NULL,
  `pump_manual_overide_data_flag` tinyint(4) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `node_mcu_data`
--

INSERT INTO `node_mcu_data` (`time_stamp`, `unc_node_mcu_unique_id`, `sump_status`, `tank_status`, `motor_status`, `debug_log`, `is_controlled_locally`, `pump_manual_overide_data_flag`) VALUES
('2023-06-05 21:27:07', '4bb7abf6d3782611339eb6fe6326b96b6b4fca3d6f7e16f33367268806c5512c', 1, 1, 1, '-1', 0, 1);

-- --------------------------------------------------------

--
-- Table structure for table `registered_node_mcu`
--

CREATE TABLE `registered_node_mcu` (
  `node_mcu_unique_id` varchar(100) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `registered_node_mcu`
--

INSERT INTO `registered_node_mcu` (`node_mcu_unique_id`) VALUES
('4bb7abf6d3782611339eb6fe6326b96b6b4fca3d6f7e16f33367268806c5512c');

-- --------------------------------------------------------

--
-- Table structure for table `user_login`
--

CREATE TABLE `user_login` (
  `user_unique_id` varchar(100) NOT NULL,
  `user_node_mcu_reference` varchar(100) NOT NULL,
  `user_full_name` char(50) NOT NULL,
  `user_password` varchar(255) NOT NULL,
  `user_email_id` varchar(100) NOT NULL,
  `user_is_admin` tinyint(1) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `user_login`
--

INSERT INTO `user_login` (`user_unique_id`, `user_node_mcu_reference`, `user_full_name`, `user_password`, `user_email_id`, `user_is_admin`) VALUES
('32a4b36497b941f4e0c478e952129baa', '4bb7abf6d3782611339eb6fe6326b96b6b4fca3d6f7e16f33367268806c5512c', 'Manoj A M', 'abecb4ad6f842ad60398ab04f0ebd245ec1ce43924a6e93c5af53683d60a876b', 'manojavarur@gmail.com', 1);

-- --------------------------------------------------------

--
-- Table structure for table `user_requests`
--

CREATE TABLE `user_requests` (
  `time_stamp` datetime DEFAULT NULL,
  `unc_node_mcu_unique_id` varchar(100) NOT NULL,
  `pump_manual_overide_request` tinyint(1) DEFAULT NULL,
  `pump_on_off_status` tinyint(1) DEFAULT NULL,
  `pump_take_over_complete_control` tinyint(1) DEFAULT NULL,
  `node_mcu_is_controled_by_user_id` varchar(100) DEFAULT NULL,
  `phpsessid` varchar(50) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Indexes for dumped tables
--

--
-- Indexes for table `cookie_data`
--
ALTER TABLE `cookie_data`
  ADD KEY `cookie_user_unique_id` (`cookie_user_unique_id`);

--
-- Indexes for table `node_mcu_data`
--
ALTER TABLE `node_mcu_data`
  ADD PRIMARY KEY (`unc_node_mcu_unique_id`);

--
-- Indexes for table `registered_node_mcu`
--
ALTER TABLE `registered_node_mcu`
  ADD PRIMARY KEY (`node_mcu_unique_id`);

--
-- Indexes for table `user_login`
--
ALTER TABLE `user_login`
  ADD PRIMARY KEY (`user_unique_id`),
  ADD KEY `user_node_mcu_reference` (`user_node_mcu_reference`);

--
-- Indexes for table `user_requests`
--
ALTER TABLE `user_requests`
  ADD PRIMARY KEY (`unc_node_mcu_unique_id`),
  ADD UNIQUE KEY `node_mcu_is_controled_by_user_id` (`node_mcu_is_controled_by_user_id`),
  ADD UNIQUE KEY `phpsessid` (`phpsessid`);

--
-- Constraints for dumped tables
--

--
-- Constraints for table `cookie_data`
--
ALTER TABLE `cookie_data`
  ADD CONSTRAINT `cookie_data_ibfk_1` FOREIGN KEY (`cookie_user_unique_id`) REFERENCES `user_login` (`user_unique_id`);

--
-- Constraints for table `node_mcu_data`
--
ALTER TABLE `node_mcu_data`
  ADD CONSTRAINT `node_mcu_data_ibfk_1` FOREIGN KEY (`unc_node_mcu_unique_id`) REFERENCES `registered_node_mcu` (`node_mcu_unique_id`);

--
-- Constraints for table `user_login`
--
ALTER TABLE `user_login`
  ADD CONSTRAINT `user_login_ibfk_1` FOREIGN KEY (`user_node_mcu_reference`) REFERENCES `registered_node_mcu` (`node_mcu_unique_id`);

--
-- Constraints for table `user_requests`
--
ALTER TABLE `user_requests`
  ADD CONSTRAINT `user_requests_ibfk_1` FOREIGN KEY (`node_mcu_is_controled_by_user_id`) REFERENCES `user_login` (`user_unique_id`),
  ADD CONSTRAINT `user_requests_ibfk_2` FOREIGN KEY (`unc_node_mcu_unique_id`) REFERENCES `registered_node_mcu` (`node_mcu_unique_id`);
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
