<template>
    <div>
        <header class="bg-blue-300 p-4 flex items-center justify-between">
            <div class="flex items-center">
                <img src="@/assets/iconka.png" alt="iconka" class="w-12 h-12 mr-2" />
                <h1 class="text-white text-xl">Корпоративный портал учета рабочего времени</h1>
            </div>
            <button class="text-white">Новый сотрудник</button>
        </header>
        <div class="flex bg-blue-100">
            <aside class="bg-blue-100 w-1/4 p-4 h-screen overflow-y-auto">
                <div class="flex items-center mb-4">
                    <svg class="w-6 h-6 mr-2 text-blue-600" fill="currentColor" viewBox="0 0 24 24">
                        <path d="M16 11c1.657 0 3-1.343 3-3S17.657 5 16 5s-3 1.343-3 3 1.343 3 3 3zm2 1h-4c-2.21 0-4 1.79-4 4v4h12v-4c0-2.21-1.79-4-4-4z" />
                        <path d="M6 11c1.657 0 3-1.343 3-3S7.657 5 6 5 3 6.343 3 8s1.343 3 3 3zm2 1H4c-2.21 0-4 1.79-4 4v4h8v-4c0-2.21-1.79-4-4-4z" />
                    </svg>
                    <span>Список сотрудников</span>
                </div>
                <ul>
                    <li v-for="(employee, index) in employees" :key="index" class="mb-2">
                        <a href="#" class="block p-2 bg-white rounded shadow">
                            {{ employee.name }}
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
                        Проводки
                    </button>
                </nav>
                <router-view />


            </main>
        </div>
    </div>
</template>

<script>
  export default {
    data() {
      return {
        currentTab: 'tasks',
        employees: Array(20).fill({ name: 'Имя Фамилия' }),
        tasks: Array(5).fill({ title: 'Название задачи' }),
        projects: Array(3).fill({ name: 'Название проекта' }),
        transactions: Array(4).fill({ detail: 'Детали проводки' })
      };
    },
  };
</script>

<style scoped>
    /* Add any additional styles here */
</style>
