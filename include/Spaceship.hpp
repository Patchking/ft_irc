/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Spaceship.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzoltan <jzoltan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 00:19:51 by jzoltan           #+#    #+#             */
/*   Updated: 2023/02/07 15:49:17 by jzoltan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#define FT_SPACESHIP_OPERATOR(arg, left, right)\
	bool operator < (arg) const {\
		return (left) < (right);\
	}\
	bool operator <= (arg) const {\
		return (left) <= (right);\
	}\
	bool operator == (arg) const {\
		return (left) == (right);\
	}\
	bool operator != (arg) const {\
		return (left) != (right);\
	}\
	bool operator > (arg) const {\
		return (left) > (right);\
	}\
	bool operator >= (arg) const {\
		return (left) >= (right);\
	}
#define FT_SPACESHIP_OPERATOR_OUTSIDE(lhs, rhs, left, right)\
	bool operator < (lhs, rhs) {\
		return (left) < (right);\
	}\
	bool operator <= (lhs, rhs) {\
		return (left) <= (right);\
	}\
	bool operator == (lhs, rhs) {\
		return (left) == (right);\
	}\
	bool operator != (lhs, rhs) {\
		return (left) != (right);\
	}\
	bool operator > (lhs, rhs) {\
		return (left) > (right);\
	}\
	bool operator >= (lhs, rhs) {\
		return (left) >= (right);\
	}

#define FT_ATTRIBUTES_SPACESHIP_OPERATOR_OUTSIDE(attributes, lhs, rhs, left, right)\
	attributes bool operator < (lhs, rhs) {\
		return (left) < (right);\
	}\
	attributes bool operator <= (lhs, rhs) {\
		return (left) <= (right);\
	}\
	attributes bool operator == (lhs, rhs) {\
		return (left) == (right);\
	}\
	attributes bool operator != (lhs, rhs) {\
		return (left) != (right);\
	}\
	attributes bool operator > (lhs, rhs) {\
		return (left) > (right);\
	}\
	attributes bool operator >= (lhs, rhs) {\
		return (left) >= (right);\
	}
