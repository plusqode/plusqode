/*
 * Copyright (C) 2026 - PlusQode - www.plusqode.com - plusqode@gmail.com
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "app/modules/pbx/pmpbx_phone_number/pmpbx_phone_number.h"
#include "dom/pdomtable.h"
#include "app/modules/core/pmmessage_box/pmmessage_box.h"

QString PMPbxPhoneNumber::$style(QString logoColor: "black", QString logoShape: "rounded") {

    QString borderRadius = "20%"; 
    if(logoShape == "square")
            borderRadius = "0px";
    else if(logoShape == "circle")
            borderRadius = "50%";


§

<style>


body {
    font-family: Arial, sans-serif;
    background: #f4f6f8;
    padding: 40px;
}

.document {
    max-width: 750px;
    margin: auto;
    background: white;
    padding: 40px;
    border-radius: 8px;
    box-shadow: 0 8px 20px rgba(0,0,0,0.08);
}

header {
    display: flex;
    justify-content: space-between;
    align-items: center;
    margin-bottom: 30px;
}

.logo {
    display: flex;
    align-items: center;
    gap: 12px;
}

.logo-box {
    width: 40px;
    height: 40px;
    background: hsl(<$=logoColor$>, 100%, 40%);
    color: white;
    display: flex;
    align-items: center;
    justify-content: center;
    font-weight: bold;
    font-size: 40px;
    border-radius: <$=borderRadius$>;
}

.logo-name {
    font-size: 40px;
    font-weight: bold;
}

.info {
    font-size: 14px;
    color: #555;
}

table {
    width: 100%;
    border-collapse: collapse;
    margin-top: 20px;
}

th {
    text-align: left;
    padding: 10px 5px;
    border-bottom: 2px solid #eee;
}

td {
    padding: 10px 5px;
    border-bottom: 1px solid #eee;
}

.total {
    text-align: right;
    margin-top: 20px;
    font-size: 25px;
    font-weight: bold;
}


</style>

§

}

QString PMPbxPhoneNumber::$head(QString title: this->modelName) {

§

<head>
  <title><$= title $></title>
  <$= PDom::$inlinetag(tag: 'link', rel: 'stylesheet', media: , 'data-turbolinks-track': true) $>

  <meta charset='UTF-8'>
  <meta name='viewport' content='width=device-width, initial-scale=1'>

  <$ PMath::initRandSequence(); QString color = QString("%1").arg(PMath::rand() % 345); $>

  <$= $style(logoColor: color, logoShape: "rounded") $>

</head>

§

}


QString PMPbxPhoneNumber::html() {

§

<!DOCTYPE html>
<html>

<$= $head() $>

<body>

<$  
$>    

<div class='document'>

    <header>
        <div class='logo'>
            <div class='logo-box'>+</div>
            <div class='logo-name'>Plus4C</div>
        </div>

        <div class='info'>
            <strong>Document #001</strong><br>
            <$= QDate::currentDate().toString("yyyy-MM-dd"); $>
        </div>
    </header>

    <div class='info'>
        <strong>Customer</strong><br> 
        Mario Rossi<br>
        Via Milano 10<br>
        20100 Milano
    </div>

    <table>
        <tr>
            <th>Description</th>
            <th>Q.ty</th>
            <th>Price</th>
            <th>Total</th>
        </tr>

        <tr>
            <td>Service</td>
            <td>1</td>
            <td>120,00 Euro</td>
            <td>120,00 Euro</td>
        </tr>
        
        <tr>
            <td>Products</td>
            <td>2</td>
            <td>40,00 Euro</td>
            <td>80,00 Euro</td>
        </tr>
    </table>

    <div class='total'>
        Total: 120,00 Euro
    </div>
    
    <div class='info'>
        <$= this->className $><br>
        <$= this->current().toString() $>
    </div>

</div>

</body>
</html>


§


}
