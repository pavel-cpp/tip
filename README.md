![TIP](icon.png)

# Text Insertion Program 

---

### **_Purpose_**
This program is designed to create and manage a database of clients<br>
and generate unique pictures (_tickets_) corresponding to each client.<br>
This software can be used for both **commercial** and **non-commercial** purposes.<br>

### **_Functionalities_**
* Generation of pictures (_tickets_)
* Database creation of any size
* Database editing similar to Excel
* Printing pictures (_tickets_)
* Saving pictures on your computer
* Copying pictures to clipboard
* Customization of _fonts_ and text _colors_

### **_How to Build_**
1. Download & Install **[Qt5][4]**

#### **Configuring**
To configure the project, add the following flags:
   ```
   "-DCMAKE_PREFIX_PATH=path/to/Qt5"
   ```

#### **Deployment**
1. Install **[Inno Setup][5]**
2. Install **[Inno Download Plugin][6]**
3. To activate deployment mode, add the following flag to the CMake configuration:
   ```
   "-DDEPLOY_DEPENDENCY=\"path/to/idp.iss\""
   ```
   or run [windows_deploy.bat][8] after building the project and enter `"path/to/idp.iss"` as an argument.

#### **Database**
To enable the program to function, you need to deploy a PostgreSQL database.<br>
Requests for creating the necessary structure are located in the [database][7] folder.

---

#### **Contacts**

[VK][1], [Telegram][2], [Discord][3]

[1]: https://vk.com/pavel.cmake
[2]: https://t.me/pavel_cpp
[3]: https://discordapp.com/users/427479608321900545/
[4]: https://cybersoft.ru/razrabotka/redaktory/208-qt.html
[5]: https://jrsoftware.org/isinfo.php
[6]: https://mitrichsoftware.wordpress.com/inno-setup-tools/inno-download-plugin/
[7]: ./deployment/database
[8]: ./deployment/deploy_windows.bat
