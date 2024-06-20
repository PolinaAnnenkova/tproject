<template>
    <div>
      <header class="bg-blue-300 p-4 flex items-center justify-between">
            <div class="flex items-center">
                <img src="@/assets/iconka.png" alt="iconka" class="w-12 h-12 mr-2" />
                <h1 class="text-white text-xl">Корпоративный портал учета рабочего времени</h1>
            </div>
            <button @click="currentTab = 'addEmployee'" class="text-white"> <router-link to="/employee">Новый сотрудник</router-link></button>
        </header>
        <div class="flex bg-blue-100">
            <aside class="bg-blue-100 w-1/4 p-4 h-screen overflow-y-auto">
                <div class="flex items-center mb-4">
                    <svg class="w-6 h-6 mr-2 text-blue-600" fill="currentColor" viewBox="0 0 24 24">
                        <path d="M16 11c1.657 0 3-1.343 3-3S17.657 5 16 5s-3 1.343-3 3 1.343 3 3 3zm2 1h-4c-2.21 0-4 1.79-4 4v4h12v-4c0-2.21-1.79-4-4-4z" />
                        <path d="M6 11c1.657 0 3-1.343 3-3S7.657 5 6 5 3 6.343 3 8s1.343 3 3 3zm2 1H4c-2.21 0-4 1.79-4 4v4h8v-4c0-2.21-1.79-4-4-4z" />
                    </svg>
                    <span><router-link to="/employee">Список сотрудников</router-link></span>
                </div>
                <ul>
                    <li v-for="(employee, index) in employees" :key="index" class="mb-2">
                        <a @click="currentTab = 'Employee'; nowIndex=index" class="block p-2 bg-white rounded shadow" href="#">
                            
                            <router-link to="/employee"> {{ employee.name }}</router-link>
                        </a>
                    </li>
                </ul>
            </aside>
            <main class="flex-1 p-4">
                <nav class="flex space-x-4 mb-4">

                    <button @click="currentTab = 'projects'"
                            :class="{'bg-blue-300 text-white': currentTab === 'projects', 'text-blue-500': currentTab !== 'projects'}"
                            class="px-4 py-2 rounded">
                        <router-link to="/projects">Проекты</router-link>
                    </button>
                    <button @click="currentTab = 'tasks'" :class="{'bg-blue-300 text-white': currentTab === 'tasks', 'text-blue-500': currentTab !== 'tasks'}"
                            class="px-4 py-2 rounded">
                        <router-link to="/tasks">Задачи</router-link>
                    </button>
                    <button @click="currentTab = 'transactions'"
                            :class="{'bg-blue-300 text-white': currentTab === 'transactions', 'text-blue-500': currentTab !== 'transactions'}"
                            class="px-4 py-2 rounded">
                        <router-link to="/transactions">Проводки</router-link>
                    </button>
                </nav>
                <router-view />
                <div v-if="currentTab === 'addEmployee'">
                    <h2 class="text-2xl mb-4">Добавление сотрудника</h2>
                    <ul>
                        <label for="name">Введите имя и фамилию нового сотрудника:    </label>
                        <input type="text"
                               v-model="newEmployees.name"
                               class=" px-3 py-1 mt-2 border border-gray-300 rounded-lg"
                               required />
                    </ul>


                    <nav class="flex space-x-4 mb-4">
                        <button @click="addEmployees();currentTab = 'empty';"
                                class="bg-blue-300 text-white px-4 py-2 rounded mb-2 mt-4 space-x-4">
                            Сохранить
                        </button>
                        <button @click="currentTab = 'empty';"
                                class="bg-blue-300 text-white px-7 py-2 rounded mb-2 mt-4 ">
                            Отмена
                        </button>
                    </nav>
                </div>
                <div v-if="currentTab === 'Employee'">
                    <h2 class="text-2xl mb-4">{{employees[nowIndex].name}}</h2>
                   
                    <nav class="flex space-x-4 mb-4">
                        <button @click="deleteEmployees(nowIndex);currentTab = 'empty';"
                                :class="{'text-blue-500': currentTab === 'tasks', 'bg-blue-300 text-white': currentTab !== 'tasks'}"
                                class="px-7 py-2 rounded mb-2 mt-4 space-x-4">
                            Удалить
                        </button>
                       
                    </nav>


                </div>
                <div v-if="currentTab === 'empty'">

                </div>

            </main>
        </div>
    </div>
  </template>

<script>
  export default {
    data() {
      return { currentTab: 'tasks',
        
        employees: [
    { name: 'Имя Фамилия1'},
    { name: 'Имя Фамилия2'},
    { name: 'Имя Фамилия3'},
    { name: 'Имя Фамилия4'},
    { name: 'Имя Фамилия5'},
    { name: 'Имя Фамилия6'}
],
  newEmployees: { name: ''},

  nowEmployee:{name:'iii'},

  nowIndex: {
             type: Number,
             default: 0
    }
      };
    },

    methods: {

    addEmployees() {
        if (this.newEmployees.name ) {
      this.employees.push({ ...this.newEmployees });
            this.newEmployees = { name: ''};
         }   
    },

      
  deleteEmployees(index) {
      this.employees.splice(index, 1);
}

  },
    
    
}
  ;
</script>

<style scoped>
    /* Add any additional styles here */
</style>