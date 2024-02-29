![TIP](icon.png)

# Text Insertion Program 

---

### **Overview**
> [!NOTE]
> This program is designed to create and manage a database of clients<br>
> and generate unique pictures (<font color='ee82ee'>_tickets_</font>) corresponding to each client.<br>
> This software can be used for both **commercial** and **non-commercial** purposes.<br>

### **Functionalities**
* Generation of pictures (_tickets_)
* Database creation of any size
* Database editing similar to Excel
* Printing pictures (_tickets_)
* Saving pictures on your computer
* Copying pictures to clipboard
* Customization of _fonts_ and text _colors_

### **How to Build**
1. Install Cmake
2. Download & Install **[Qt5][4]**
3. ```sh
   cmake -DCMAKE_BUILD_TYPE={type} -DCMAKE_PREFIX_PATH=path/to/Qt5 -G {generator} -B ./cmake-build-{type} 
   cmake --build ./cmake-build-debug --target TIP -j 14
   ```

#### **Deployment**
1. Install **[Inno Setup][5]**
2. Install **[Inno Download Plugin][6]**
3. To activate deployment mode, add the following flag to the CMake configuration:
   ```sh
   cmake -DCMAKE_BUILD_TYPE={type} -DCMAKE_PREFIX_PATH=path/to/Qt5 "-DDEPLOY_DEPENDENCY=\"path/to/idp.iss\"" -G {generator} -B ./cmake-build-{type} 
   cmake --build ./cmake-build-debug --target TIP -j 14
   ```
   or run [windows_deploy.bat][8] after building the project and enter `"path/to/idp.iss"` as an argument.

#### **Database**
> [!IMPORTANT]
> To enable the program to function, you need to deploy a PostgreSQL database.<br>
> Requests for creating the necessary structure are located in the [database][7] folder.

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
