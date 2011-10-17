-- phpMyAdmin SQL Dump
-- version 3.4.5
-- http://www.phpmyadmin.net
--
-- Хост: localhost
-- Время создания: Окт 17 2011 г., 23:10
-- Версия сервера: 5.1.56
-- Версия PHP: 5.3.8-pl0-gentoo

SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- База данных: `game`
--

-- --------------------------------------------------------

--
-- Структура таблицы `Attribute`
--

CREATE TABLE IF NOT EXISTS `Attribute` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `title` varchar(60) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM  DEFAULT CHARSET=utf8 AUTO_INCREMENT=3 ;

--
-- Дамп данных таблицы `Attribute`
--

INSERT INTO `Attribute` (`id`, `title`) VALUES
(1, 'Мин. урон'),
(2, 'Макс. урон');

-- --------------------------------------------------------

--
-- Структура таблицы `Character`
--

CREATE TABLE IF NOT EXISTS `Character` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `idUser` int(11) NOT NULL,
  `name` varchar(70) NOT NULL,
  `level` int(11) NOT NULL,
  `money` int(11) NOT NULL,
  `coordinateX` tinyint(4) NOT NULL,
  `coordinateY` tinyint(4) NOT NULL,
  `avatar` varchar(50) NOT NULL,
  PRIMARY KEY (`id`),
  KEY `idUser` (`idUser`,`level`)
) ENGINE=MyISAM  DEFAULT CHARSET=utf8 AUTO_INCREMENT=2 ;

--
-- Дамп данных таблицы `Character`
--

INSERT INTO `Character` (`id`, `idUser`, `name`, `level`, `money`, `coordinateX`, `coordinateY`, `avatar`) VALUES
(1, 1, 'ismd', 1, 10, 2, 2, '');

-- --------------------------------------------------------

--
-- Структура таблицы `CharacterItem`
--

CREATE TABLE IF NOT EXISTS `CharacterItem` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `idCharacter` int(11) NOT NULL,
  `idItem` int(11) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM  DEFAULT CHARSET=utf8 AUTO_INCREMENT=3 ;

--
-- Дамп данных таблицы `CharacterItem`
--

INSERT INTO `CharacterItem` (`id`, `idCharacter`, `idItem`) VALUES
(1, 1, 1),
(2, 1, 2);

-- --------------------------------------------------------

--
-- Структура таблицы `Item`
--

CREATE TABLE IF NOT EXISTS `Item` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `title` varchar(70) NOT NULL,
  `idType` int(11) NOT NULL,
  `price` int(11) NOT NULL,
  `description` text,
  PRIMARY KEY (`id`),
  UNIQUE KEY `title` (`title`),
  KEY `idType` (`idType`),
  KEY `price` (`price`)
) ENGINE=MyISAM  DEFAULT CHARSET=utf8 AUTO_INCREMENT=3 ;

--
-- Дамп данных таблицы `Item`
--

INSERT INTO `Item` (`id`, `title`, `idType`, `price`, `description`) VALUES
(1, 'Простой меч', 1, 2, 'Этот маленький меч поможет тебе против котов!'),
(2, 'Обтягивающие джинсы', 3, 3, NULL);

-- --------------------------------------------------------

--
-- Структура таблицы `ItemAttribute`
--

CREATE TABLE IF NOT EXISTS `ItemAttribute` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `iditem` int(11) NOT NULL,
  `idAttribute` int(11) NOT NULL,
  `value` int(11) NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `ItemAttribute` (`iditem`,`idAttribute`),
  KEY `iditem` (`iditem`)
) ENGINE=MyISAM  DEFAULT CHARSET=utf8 AUTO_INCREMENT=3 ;

--
-- Дамп данных таблицы `ItemAttribute`
--

INSERT INTO `ItemAttribute` (`id`, `iditem`, `idAttribute`, `value`) VALUES
(1, 1, 1, 3),
(2, 1, 2, 5);

-- --------------------------------------------------------

--
-- Структура таблицы `ItemType`
--

CREATE TABLE IF NOT EXISTS `ItemType` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `title` varchar(50) NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `title` (`title`)
) ENGINE=MyISAM  DEFAULT CHARSET=utf8 AUTO_INCREMENT=8 ;

--
-- Дамп данных таблицы `ItemType`
--

INSERT INTO `ItemType` (`id`, `title`) VALUES
(1, 'Одноручный меч'),
(2, 'Одноручный топор'),
(3, 'Штаны'),
(4, 'Обувь'),
(5, 'Одежда'),
(6, 'Голова'),
(7, 'Щит');

-- --------------------------------------------------------

--
-- Структура таблицы `Mob`
--

CREATE TABLE IF NOT EXISTS `Mob` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `title` varchar(40) NOT NULL,
  `hp` int(11) NOT NULL,
  `damage` int(11) NOT NULL,
  `maxOnMap` int(11) NOT NULL,
  `experience` int(11) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM  DEFAULT CHARSET=utf8 AUTO_INCREMENT=4 ;

--
-- Дамп данных таблицы `Mob`
--

INSERT INTO `Mob` (`id`, `title`, `hp`, `damage`, `maxOnMap`, `experience`) VALUES
(1, 'Кот', 10, 1, 1, 1),
(2, 'Собака', 15, 3, 2, 3),
(3, 'Кот Вася', 12, 10, 1, 7);

-- --------------------------------------------------------

--
-- Структура таблицы `MobCell`
--

CREATE TABLE IF NOT EXISTS `MobCell` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `idMob` int(11) NOT NULL,
  `coordinateX` int(11) NOT NULL,
  `coordinateY` int(11) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM  DEFAULT CHARSET=utf8 AUTO_INCREMENT=6 ;

--
-- Дамп данных таблицы `MobCell`
--

INSERT INTO `MobCell` (`id`, `idMob`, `coordinateX`, `coordinateY`) VALUES
(1, 1, 2, 1),
(2, 1, 2, 2),
(3, 2, 1, 2),
(4, 2, 2, 2),
(5, 3, 1, 1);

-- --------------------------------------------------------

--
-- Структура таблицы `NpcItem`
--

CREATE TABLE IF NOT EXISTS `NpcItem` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `idNpc` int(11) NOT NULL,
  `idItem` int(11) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM  DEFAULT CHARSET=utf8 AUTO_INCREMENT=3 ;

--
-- Дамп данных таблицы `NpcItem`
--

INSERT INTO `NpcItem` (`id`, `idNpc`, `idItem`) VALUES
(1, 1, 1),
(2, 1, 2);

-- --------------------------------------------------------

--
-- Структура таблицы `User`
--

CREATE TABLE IF NOT EXISTS `User` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `login` varchar(40) NOT NULL,
  `password` varchar(32) NOT NULL,
  `email` varchar(50) NOT NULL,
  `info` text,
  `site` varchar(50) DEFAULT NULL,
  `regDateTime` datetime NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `login` (`login`),
  UNIQUE KEY `email` (`email`)
) ENGINE=MyISAM  DEFAULT CHARSET=utf8 AUTO_INCREMENT=3 ;

--
-- Дамп данных таблицы `User`
--

INSERT INTO `User` (`id`, `login`, `password`, `email`, `info`, `site`, `regDateTime`) VALUES
(1, 'ismd', '123', 'asd@asd.ru', NULL, NULL, '0000-00-00 00:00:00'),
(2, 'ismd1', 'c4ca4238a0b923820dcc509a6f75849b', '', NULL, NULL, '0000-00-00 00:00:00');

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
