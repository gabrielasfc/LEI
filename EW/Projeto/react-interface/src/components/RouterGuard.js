import React from 'react';
import { Navigate } from 'react-router-dom';
import jwt_decode from 'jwt-decode'
import Cookies from 'js-cookie'
import NoPage from '../pages/NoPage';

function RouterGuard({children, level}) {
    function hasJWT() {        
        var token = localStorage.getItem('token')
        var decodedToken

        if(token){
            try{
                decodedToken = jwt_decode(token)
                if(Date.now() >= decodedToken.exp * 1000) return 0
                else if(decodedToken.level < level) return -1
                else return 1
            }
            catch (error){}
        }
        else if(Cookies.get('token')){
            token = Cookies.get('token')
            try{
                decodedToken = jwt_decode(token)
                if(Date.now() >= decodedToken.exp * 1000) return 0
                else if(decodedToken.level < level) return -1
                else {
                    localStorage.setItem('token', token)
                    return 1
                }
            }
            catch (error){}
        }

        return 0
    }
  
    if(hasJWT() === 0) return <Navigate to="/login"/>;
    else if(hasJWT() === -1) return <NoPage/>; // Podemos melhorar
    else return children;
 };

export default RouterGuard;