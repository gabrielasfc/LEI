import ReactDOM from "react-dom/client"
import { BrowserRouter, Routes, Route } from "react-router-dom"
import Login from "./pages/Login"
import Register from "./pages/Register"
import NoPage from "./pages/NoPage"
import Home from "./pages/Home"
import Record from "./pages/Record"
import Edit from "./pages/Edit"
import Insert from "./pages/Insert"
import Profile from "./pages/Profile"
import Dashboard from "./pages/Dashboard"
import Favorites from "./pages/Favorites"
import Descricao from "./pages/Descricao"
import RouterGuard from "./components/RouterGuard"
import 'bootstrap/dist/css/bootstrap.min.css'
import 'react-toastify/dist/ReactToastify.css'

export default function App() {
  return (
    <BrowserRouter>
        <Routes>
          <Route path="/login" element={<Login/>}/>
          <Route path="/register" element={ <Register/> }/>
          <Route path="/" element={<RouterGuard level="10"> <Home/> </RouterGuard>}/>
          <Route path="/profile" element={<RouterGuard level="10"> <Profile/> </RouterGuard>}/>
          <Route path="/favorites" element={<RouterGuard level="10"> <Favorites/> </RouterGuard>}/>
          <Route path="/descricoes" element={<RouterGuard level="10"> <Descricao/> </RouterGuard>}/>
          <Route path="/insert" element={<RouterGuard level="20"> <Insert/> </RouterGuard>}/>
          <Route path="/dashboard" element={<RouterGuard level="100"> <Dashboard/> </RouterGuard>}/>
          <Route path="/edit/:id" element={<RouterGuard level="100"> <Edit/> </RouterGuard>}/>
          <Route path="/:id" element={<RouterGuard level="10"> <Record/> </RouterGuard>}/>
          <Route path="*" element={<NoPage/>}/>  // Proteger esta merda
        </Routes>
    </BrowserRouter>
  )
}

const root = ReactDOM.createRoot(document.getElementById('root'))
root.render(<App />)